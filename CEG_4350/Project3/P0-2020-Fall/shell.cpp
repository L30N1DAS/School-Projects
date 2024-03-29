/*
 * shell.C -- CEG433 File Sys Project shell
 * pmateti@wright.edu
 */

#include "fs33types.hpp"

extern MountEntry *mtab;
extern VNIN cwdVNIN;
FileVolume * fv;                // Suspicious!
Directory * wd;                 // Suspicious!

#define nArgsMax 10
char types[1+nArgsMax];   // +1 for \0

/* An Arg-ument for one of our commands is either a "word" (a null
 * terminated string), or an unsigned integer.  We store both
 * representations of the argument. */

class Arg {
public:
  char *s;
  uint u;
} arg[nArgsMax];

uint nArgs = 0;

uint TODO()
{
  printf("to be done!\n");
  return 0;
}

uint TODO(char *p)
{
  printf("%s to be done!\n", p);
  return 0;
}

uint isDigit(char c)
{
  return '0' <= c && c <= '9';
}

uint isAlphaNumDot(char c)
{
  return c == '.' || 'a' <= c && c <= 'z'
      || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9';
}

int toNum(const char *p)
{
  return (p != 0 && '0' <= *p && *p <= '9' ? atoi(p) : 0);
}

SimDisk * mkSimDisk(byte *name)
{
  SimDisk * simDisk = new SimDisk(name, 0);
  if (simDisk->nSectorsPerDisk == 0) {
    printf("Failed to find/create simDisk named %s\n", name);
    delete simDisk;
    simDisk = 0;
  }
  return simDisk;
}

void doMakeDisk(Arg * a)
{
  SimDisk * simDisk = mkSimDisk((byte *) a[0].s);
  if (simDisk == 0)
    return;
  printf("new SimDisk(%s) = %p, nSectorsPerDisk=%d,"
         "nBytesPerSector=%d, simDiskNum=%d)\n",
   simDisk->name, (void*) simDisk, simDisk->nSectorsPerDisk,
         simDisk->nBytesPerSector, simDisk->simDiskNum);
  delete simDisk;
}

void doWriteDisk(Arg * a)
{
  SimDisk * simDisk = mkSimDisk((byte *) a[0].s);
  if (simDisk == 0)
    return;
  char *st = a[2].s;    // arbitrary word
  if (st == 0)      // if it is NULL, we use ...
    st = "CEG433/633/Mateti";
  char buf[1024];   // assuming nBytesPerSectorMAX < 1024
  for (uint m = strlen(st), n = 0; n < 1024 - m; n += m)
    memcpy(buf + n, st, m); // fill with several copies of st
  uint r = simDisk->writeSector(a[1].u, (byte *) buf);
  printf("write433disk(%d, %s...) == %d to Disk %s\n", a[1].u, st, r, a[0].s);
  delete simDisk;
}

void doReadDisk(Arg * a)
{
  SimDisk * simDisk = mkSimDisk((byte *) a[0].s);
  if (simDisk == 0)
    return;
  char buf[1024];   // assuming nBytesPerSectorMAX < 1024
  uint r = simDisk->readSector(a[1].u, (byte *) buf);
  buf[10] = 0;      // sentinel
  printf("read433disk(%d, %s...) = %d from Disk %s\n", a[1].u, buf, r, a[0].s);
  delete simDisk;
}

void doQuit(Arg * a)
{
  exit(0);
}

void doEcho(Arg * a)
{
  printf("%s#%d, %s#%d, %s#%d, %s#%d\n", a[0].s, a[0].u,
         a[1].s, a[1].u, a[2].s, a[2].u, a[3].s, a[3].u);
}

void doMakeFV(Arg * a)
{
  SimDisk * simDisk = mkSimDisk((byte *) a[0].s);
  if (simDisk == 0)
    return;
  fv = simDisk->make33fv();
  printf("make33fv() = %p, Name == %s, Disk# == %d\n",
   (void*) fv, a[0].s, simDisk->simDiskNum);

  if (fv) {
    wd = new Directory(fv, 1, 0);
    cwdVNIN = mkVNIN(simDisk->simDiskNum, 1);
  }
}

void doCopyTo(byte* from, byte* to)
{
  uint r = fv->write33file(to, from);
  printf("write33file(%s, %s) == %d\n", to, from, r);
}

void doCopyFrom(byte* from, byte* to)
{
  uint r = fv->read33file(to, from);
  printf("read33file(%s, %s) == %d\n", to, from, r);
}

void doCopy33(byte* from, byte* to)
{
  uint r = fv->copy33file(to, from);
  printf("copy33file(%s, %s) == %d\n", to, from, r);
}

void doCopy(Arg * a)
{
  byte* to = (byte *) a[0].s;
  byte* from = (byte *) a[1].s;

  if (a[0].s[0] == '@' && a[1].s[0] != '@') {
    doCopyTo(from, (to + 1));
  }
  else if (a[0].s[0] != '@' && a[1].s[0] == '@') {
    doCopyFrom((from + 1), to);
  }
  else if (a[0].s[0] != '@' && a[1].s[0] != '@') {
    doCopy33(from, to);
  }
  else {
    puts("Wrong arguments to cp.");
  }
}

void doPwd(Arg * a)
{
  Directory* curDir = wd;
  Directory* parentDir;
  uint parentINode = 0;
  std::vector<std::string> pathVec;
  std::string path = "";

  while (parentINode != 1) {
    parentINode = curDir->iNumberOf((byte *) "..");
    parentDir = new Directory(fv, parentINode, 0);
    pathVec.push_back((char *) parentDir->nameOf(curDir->nInode));
    if (curDir != wd) {
      delete(curDir);
    }
    curDir = parentDir;
  }
  delete(parentDir);

  for (int i = pathVec.size() - 1; i >= 0; i--) {
    path = path + "/" + pathVec[i];
  }

  std::cout << path << std::endl;
}

std::string getAbsPath(Directory * curDir)
{
  Directory* parentDir;
  uint parentINode = 0;
  std::vector<std::string> pathVec;
  std::string path = "";

  while (parentINode != 1) {
    parentINode = curDir->iNumberOf((byte *) "..");
    parentDir = new Directory(fv, parentINode, 0);
    pathVec.push_back((char *) parentDir->nameOf(curDir->nInode));
    if (curDir != wd) {
      delete(curDir);
    }
    curDir = parentDir;
  }
  delete(parentDir);

  for (int i = pathVec.size() - 1; i >= 0; i--) {
    path = path + "/" + pathVec[i];
  }

  return path;
}

void doLsLong(Arg * a)
{
  printf("\nDirectory listing for disk %s, cwdVNIN == 0x%0lx begins:\n",
   wd->fv->simDisk->name, (ulong) cwdVNIN);
  wd->ls();                     // Suspicious!
  printf("Directory listing ends.\n");
}

void doLsName(Arg * a)
{
  Directory* curDir;
  uint iNode = wd->iNumberOf((byte *) a[0].s);
  if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
    curDir = wd;
    wd = new Directory(fv, iNode, 0);
    doLsLong(a);
    delete(wd);
    wd = curDir;
  }
  else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeOrdinary) {
    printf("%7d %crw-rw-rw-    1 yourName yourGroup %7d Jul 15 12:34 %s\n",
	     iNode, '-', wd->fv->inodes.getFileSize(iNode), a[0].s);
  }
  else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeSoftLink) {
    uint bn = fv->inodes.getBlockNumber(iNode, 0);
    byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
    fv->readBlock(bn, blockData);
    if (blockData[1] == '.') {
      blockData+=2;
    }
    printf("%7d %crw-rw-rw-    1 yourName yourGroup %7d Jul 15 12:34 %s -> %s\n",
	     iNode, 'l', wd->fv->inodes.getFileSize(iNode), a[0].s, (char *) blockData);
  }
}

void doLsNameRecursiveHelper(const char * name) {
  uint iNode = wd->iNumberOf((byte *) name);
  if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
    wd = new Directory(fv, iNode, 0);
    doPwd((Arg *) name);
    doLsLong((Arg *) name);
  }
  else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeOrdinary) {
    printf("%7d %crw-rw-rw-    1 yourName yourGroup %7d Jul 15 12:34 %s\n",
	     iNode, '-', wd->fv->inodes.getFileSize(iNode), name);
    return;
  }
  else if (iNode == 0) {
    printf("File/Directory not found.\n");
    return;
  }
  Directory * curDir = wd;
  std::vector<std::string> entriesVec = wd->getEntries();
  for (long unsigned int i = 0; i < entriesVec.size(); i++) {
    const char * vecEntry = entriesVec[i].c_str();
    iNode = wd->iNumberOf((byte *) vecEntry);
    if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
      doLsNameRecursiveHelper(vecEntry);
      wd = curDir;
    }
  }
  delete(wd);
}

void doLsNameRecursive(Arg * a) {
  if (strcmp(a[0].s, "-lR") == 0 || strcmp(a[0].s, "-Rl") == 0) {
    Directory * curDir = wd;
    doLsNameRecursiveHelper(a[1].s);
    wd = curDir;
    return;
  }
  printf("Incorrect flag for recursive ls.\n");
}

uint findNumSlashes(char* path) {
  char* findSlashes;
  uint numSlashes = 0;
  findSlashes = strchr(path, '/');
  while (findSlashes != NULL) {
    numSlashes++;
    findSlashes = strchr(findSlashes+1, '/');
  }
  return numSlashes;
}

void updatePath(char* path, std::string newPath) {
  for (long unsigned int i = 0; i < newPath.length(); i++) {
    path[i] = newPath[i];
  }
  path[newPath.length()] = '\0';
}

bool fixPath (char* path) {
  for (int i = strlen(path) - 1; i >= 0; i--) {
    if (path[i] == '/') {
      path[i] = 0;
    }
    else {
      break;
    }
  }
  for (long unsigned int i = 0; i < strlen(path); i++) {
    if (path[i] == '/' && path[i+1] == '/') {
      return false;
    }
  }
  return true;
}

std::vector<std::string> getPathVec(char* path) {
  std::vector<std::string> pathVec;
  if (!fixPath(path)) {
    return pathVec;
  }
  std::string remPathStr;
  if (path[0] != '/') {
    remPathStr = path;
    remPathStr = "/" + remPathStr;
    updatePath(path, remPathStr);
  }
  uint numSlashes = findNumSlashes(path);
  for (uint i = 0; i < numSlashes; i++) {
    pathVec.push_back(strtok(path, "/"));
    char* remPathChar = strtok(0, " \t");
    if (remPathChar == 0 && i == numSlashes - 1) {
      break;
    }
    remPathStr = remPathChar;
    remPathStr = "/" + remPathStr;
    updatePath(path, remPathStr);
  }
  return pathVec;
}

std::vector<std::string> doMvPath(char * path, bool& invalidPath, bool& IsFile, bool& exists);

uint getLinkType(std::string path) {
  Directory * startDir = new Directory(fv, wd->nInode, 0);
  char charPath[path.length() + 1]; 
	strcpy(charPath, path.c_str()); 
  bool tmp;
  std::vector<std::string> pathVec = doMvPath(charPath, tmp, tmp, tmp);
  Directory * pathDir = wd;
  wd = startDir;
  const char * lastEntry = pathVec[pathVec.size() - 1].c_str();
  uint in = pathDir->iNumberOf((byte *) lastEntry);
  if (pathDir->fv->inodes.getType(in) == iTypeOrdinary) {
    return iTypeOrdinary;
  }
  else if (pathDir->fv->inodes.getType(in) == iTypeDirectory) {
    return iTypeDirectory;
  }
  else if (pathDir->fv->inodes.getType(in) == iTypeSoftLink) {
    uint bn = fv->inodes.getBlockNumber(in, 0);
    byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
    fv->readBlock(bn, blockData);
    if (blockData[1] == '.') {
      blockData+=2;
    }
    std::string pathStr = (char *) blockData;
    return getLinkType(pathStr);
  }
  else return 0;
}

bool successiveCD(char * path)
{
  bool toRoot = false;
  bool afterRoot = true;
  printf("abugabuga\n");
  Directory* startDir = new Directory(fv, wd->nInode, 0);
  if (path[0] == '/') {
    toRoot = true;
    if (path[1] == 0) {
      afterRoot = false;
    }
    else if (path[1] == '/') {
      afterRoot = false;
      for (long unsigned int i = 0; i < strlen(path); i++) {
        if (path[i] != '/') {
          toRoot = false;
          return false;
        }
        else {
          toRoot = true;
        }
      }
    }
  }
  if (toRoot) {
    Directory* childDir = wd;
    uint rootINode = 0;
    while (rootINode != 1) {
      rootINode = childDir->iNumberOf((byte *) "..");
      wd = new Directory(fv, rootINode, 0);
      if (childDir != startDir) {
        delete(childDir);
      }
      childDir = wd;
    }
  }
  if (afterRoot) {
    std::vector<std::string> pathVec = getPathVec(path);
    uint iNode = 0;
    const char* pathEntry;
    for (long unsigned int i = 0; i < pathVec.size(); i++) {
      pathEntry = pathVec[i].c_str(); // https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
      iNode = wd->iNumberOf((byte *) pathEntry);
      if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
        Directory* tmp = wd;
        wd = new Directory(fv, iNode, 0);
        if (tmp != startDir) {
          delete(tmp);
        }
      }
      else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeSoftLink) {
        uint bn = fv->inodes.getBlockNumber(iNode, 0);
        byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
        fv->readBlock(bn, blockData);
        if (blockData[1] == '.') {
          blockData+=2;
        }
        std::string pathStr = (char *) blockData;
        uint type = getLinkType(pathStr);
        if (type == iTypeDirectory) {
          successiveCD((char *) blockData);
        }
        else {
          return false;
        }
      }
      else {
        if (wd != startDir) {
          delete(wd);
          wd = startDir;
        }
        return false;
      }
    }
    if (pathVec.size() == 0) {
      if (wd != startDir) {
        delete(wd);
        wd = startDir;
      }
      return false;
    }
  }
  if (wd != startDir) {
    delete(startDir);
  }
  return true;
}

std::vector<std::string> doMvPath(char * path, bool& invalidPath, bool& IsFile, bool& exists)
{
  bool toRoot = false;
  bool afterRoot = true;
  Directory* startDir = new Directory(fv, wd->nInode, 0);
  if (path[0] == '/') {
    toRoot = true;
    if (path[1] == 0) {
      afterRoot = false;
    }
    else if (path[1] == '/') {
      afterRoot = false;
      for (long unsigned int i = 0; i < strlen(path); i++) {
        if (path[i] != '/') {
          toRoot = false;
          break;
        }
        else {
          toRoot = true;
        }
      }
    }
  }
  if (toRoot) {
    Directory* childDir = wd;
    uint rootINode = 0;
    while (rootINode != 1) {
      rootINode = childDir->iNumberOf((byte *) "..");
      wd = new Directory(fv, rootINode, 0);
      if (childDir != startDir) {
        delete(childDir);
      }
      childDir = wd;
    }
  }
  std::vector<std::string> pathVec;
  if (afterRoot) {
    pathVec = getPathVec(path);
    uint iNode = 0;
    const char* pathEntry;
    for (long unsigned int i = 0; i < pathVec.size(); i++) {
      pathEntry = pathVec[i].c_str(); // https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
      iNode = wd->iNumberOf((byte *) pathEntry);
      if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
        if (i != pathVec.size() - 1) {
          Directory* tmp = wd;
          wd = new Directory(fv, iNode, 0);
          if (tmp != startDir) {
            delete(tmp);
          }
        }
      }
      else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeOrdinary && i == pathVec.size() - 1) {
        IsFile = true;
        break;
      }
      else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeSoftLink) {
        if (i != pathVec.size() - 1) {
          uint bn = fv->inodes.getBlockNumber(iNode, 0);
          byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
          fv->readBlock(bn, blockData);
          if (blockData[1] == '.') {
            blockData+=2;
          }
          std::string pathStr = (char *) blockData;
          uint type = getLinkType(pathStr);
          if (type == iTypeDirectory) {
            bool success = successiveCD((char *) blockData);
            if (!success) {
              invalidPath = true;
              break;
            }
          }
          else {
            invalidPath = true;
            break;
          }
        }
      }
      else if (iNode == 0 && i == pathVec.size() - 1) {
        exists = false;
      }
      else {
        invalidPath = true;
        break;
      }
    }
    if (pathVec.size() == 0) {
      invalidPath = true;
    }
  }
  return pathVec;
}

void doRm(Arg * a)
{
  Directory * startDir = new Directory(fv, wd->nInode, 0);
  bool tmp;

  std::vector<std::string> pathVec = doMvPath(a[0].s, tmp, tmp, tmp);
  Directory* remDirParent = wd;
  wd = startDir;

  const char* deleteEntity = pathVec[pathVec.size() - 1].c_str();
  uint in = remDirParent->iNumberOf((byte *) deleteEntity);

  if (in == 0) {
    printf("File/Directory not found.\n");
    delete(remDirParent);
    return;
  }
  uint numContents = 0;
  if (remDirParent->fv->inodes.getType(in) == iTypeDirectory) {
    numContents = wd->lsInvis(in);
  }
  if (remDirParent->fv->inodes.getType(in) == iTypeDirectory && numContents == 0) {
    in = remDirParent->deleteFile((byte *) deleteEntity, 1);
    printf("Successfully removed directory '%s' with inode %d and %d entries.\n", deleteEntity, in, numContents);
  }
  else if (remDirParent->fv->inodes.getType(in) == iTypeDirectory && numContents != 0) {
    printf("Unable to remove directory '%s' with inode %d and %d entries.\n", deleteEntity, in, numContents);
  }
  else if (remDirParent->fv->inodes.getType(in) == iTypeOrdinary) {
    int numLinks = fv->inodes.getLinkCount(in);
    int flag;
    if (numLinks == 0) {
      flag = 1;
    }
    else if (numLinks > 0) {
      flag = 0;
    }
    in = remDirParent->deleteFile((byte *) deleteEntity, flag);
    fv->inodes.incLinkCount(in, -1);
    printf("Successfully removed file '%s' with inode %d.\n", deleteEntity, in);
    printf("Resulting link count for inode %d: %d\n", in, fv->inodes.getLinkCount(in));
  }
  else if (remDirParent->fv->inodes.getType(in) == iTypeSoftLink) {
    int numLinks = fv->inodes.getLinkCount(in);
    int flag;
    if (numLinks == 0) {
      flag = 1;
    }
    else if (numLinks > 0) {
      flag = 0;
    }
    in = remDirParent->deleteFile((byte *) deleteEntity, flag);
    fv->inodes.incLinkCount(in, -1);
    printf("Successfully removed symbolic link '%s' with inode %d.\n", deleteEntity, in);
    printf("Resulting link count for inode %d: %d\n", in, fv->inodes.getLinkCount(in));
  }
  delete(remDirParent);
}

void doRmRecursiveHelper(const char * name) {
  uint iNode = wd->iNumberOf((byte *) name);
  if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
    wd = new Directory(fv, iNode, 0);
  }
  else if (iNode != 0 && (wd->fv->inodes.getType(iNode) == iTypeOrdinary || wd->fv->inodes.getType(iNode) == iTypeSoftLink)) {
    return;
  }
  else if (iNode == 0) {
    printf("File/Directory not found.\n");
    return;
  }
  Directory * curDir = wd;
  std::vector<std::string> entriesVec = wd->getEntries();
  for (long unsigned int i = 0; i < entriesVec.size(); i++) {
    const char * vecEntry = entriesVec[i].c_str();
    iNode = wd->iNumberOf((byte *) vecEntry);
    if (iNode != 0) {
      doRmRecursiveHelper(vecEntry);
      wd = curDir;
      wd->deleteFile((byte *) vecEntry, 1);
    }
  }
  delete(wd);
}

void doRmRecursive(Arg * a) {
  if (strcmp(a[0].s, "-fr") == 0 || strcmp(a[0].s, "-rf") == 0) {
    Directory * curDir = wd;
    doRmRecursiveHelper(a[1].s);
    wd = curDir;
    wd->deleteFile((byte *) a[1].s, 1);
    return;
  }
  printf("Incorrect flag for recursive rm.\n");
}

void doInode(Arg * a)
{
  uint ni = a[0].u;
  wd->fv->inodes.show(ni);
}

void doInodeName(Arg * a)
{
  uint iNode = wd->iNumberOf((byte *) a[0].s);
  wd->fv->inodes.show(iNode);
}

void doMkDir(Arg * a)
{
  uint in = wd->iNumberOf((byte *) a[0].s);
  if (in != 0) {
    printf("%s already exists.\n", a[0].s);
    return;
  }
  in = wd->createFile((byte *) a[0].s, 1);
  printf("inode: %d\n", in);
}

void doTouch(Arg * a) {
  uint in = wd->iNumberOf((byte *) a[0].s);
  if (in != 0) {
    printf("'%s' already exists.\n", a[0].s);
    return;
  }
  in = wd->createFile((byte *) a[0].s, 0);
  printf("inode: %d\n", in);
}

void doChDir(Arg * a)
{
  bool toRoot;
  bool afterRoot = true;
  Directory* startDir = new Directory(fv, wd->nInode, 0);
  if (a[0].s[0] == '/') {
    toRoot = true;
    if (a[0].s[1] == 0) {
      afterRoot = false;
      printf("Changing directory to root.\n");
    }
    else if (a[0].s[1] == '/') {
      afterRoot = false;
      for (long unsigned int i = 0; i < strlen(a[0].s); i++) {
        if (a[0].s[i] != '/') {
          toRoot = false;
          printf("Changing directory failed.\n");
          break;
        }
        else {
          toRoot = true;
        }
      }
      if (toRoot) {
        printf("Changing directory to root.\n");
      }
    }
  }
  if (toRoot) {
    Directory* childDir = wd;
    uint rootINode = 0;
    while (rootINode != 1) {
      rootINode = childDir->iNumberOf((byte *) "..");
      wd = new Directory(fv, rootINode, 0);
      if (childDir != startDir) {
        delete(childDir);
      }
      childDir = wd;
    }
  }
  if (afterRoot) {
    std::vector<std::string> pathVec = getPathVec(a[0].s);
    uint iNode = 0;
    const char* pathEntry;
    for (long unsigned int i = 0; i < pathVec.size(); i++) {
      pathEntry = pathVec[i].c_str(); // https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
      iNode = wd->iNumberOf((byte *) pathEntry);
      if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
        Directory* tmp = wd;
        wd = new Directory(fv, iNode, 0);
        if (tmp != startDir) {
          delete(tmp);
        }
      }
      else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeSoftLink) {
        uint bn = fv->inodes.getBlockNumber(iNode, 0);
        byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
        fv->readBlock(bn, blockData);
        if (blockData[1] == '.') {
          blockData+=2;
        }
        std::string pathStr = (char *) blockData;
        uint type = getLinkType(pathStr);
        if (type == iTypeDirectory) {
          bool success = successiveCD((char *) blockData);
          if (!success) {
            printf("Changing directory failed.\n");
            if (wd != startDir) {
              delete(wd);
              wd = startDir;
            }
          }
        }
        else {
          printf("Changing directory failed.\n");
          if (wd != startDir) {
            delete(wd);// here
            wd = startDir;
          }
        }
      }
      else {
        printf("Changing directory failed.\n");
        if (wd != startDir) {
          delete(wd);
          wd = startDir;
        }
        break;
      }
    }
    if (pathVec.size() == 0) {
      printf("Changing directory failed.\n");
      if (wd != startDir) {
        delete(wd);
        wd = startDir;
      }
    }
  }
  if (wd != startDir) {
    delete(startDir);
  }
  printf("Current working directory: ");
  doPwd(a);
}

bool fileInPath(std::vector<std::string> pathVec, uint iNode) {
  Directory* dir = wd;
  uint pathINode;
  const char* pathEntry;
  for (long unsigned int i = 0; i < pathVec.size(); i++) {
    pathEntry = pathVec[i].c_str(); // https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
    pathINode = dir->iNumberOf((byte *) pathEntry);
    if (pathINode == iNode) {
      if (dir != wd) {
        delete(dir);
      }
      return true;
    }
    Directory* tmp = dir;
    dir = new Directory(fv, pathINode, 0);
    if (tmp != wd) {
      delete(tmp);
    }
  }
  return false;
}

void doMv(Arg * a)
{
  Directory * startDir = new Directory(fv, wd->nInode, 0);
  bool sourceInvalidPath = false;
  bool sourceIsFile = false;
  bool sourceExists = true;
  bool destInvalidPath = false;
  bool destIsFile = false;
  bool destExists = true;

  if (a[0].s[0] == '.') {
    printf("Cannot move '.' or '..'.\n");
    return;
  }

  // https://stackoverflow.com/questions/16515582/how-to-perform-a-deep-copy-of-a-char and 
  // https://stackoverflow.com/questions/481673/make-a-copy-of-a-char
  char* destPath = new char[strlen(a[1].s)+1]; // allocate for string and ending \0
  strcpy(destPath, a[1].s);
  // end citation

  std::vector<std::string> sourceVec = doMvPath(a[0].s, sourceInvalidPath, sourceIsFile, sourceExists);
  Directory* sourceDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);
  if (sourceVec.size() == 0) {
    delete(destPath);
    if (sourceDir != wd) {
      delete(sourceDir);
    }
    printf("Cannot move or rename root.\n");
    return;
  }
  std::vector<std::string> destVec = doMvPath(destPath, destInvalidPath, destIsFile, destExists);
  if (destVec.size() == 0) {
    destVec.push_back(".");
  }
  delete(destPath);
  Directory* destDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);

  if (!sourceExists || sourceInvalidPath || destInvalidPath || (destExists && destIsFile)) {
    if (sourceDir != wd) {
      delete(sourceDir);
    }
    if (destDir != wd) {
      delete(destDir);
    }
    printf("Move/Rename failed.\n");
    return;
  }
  else if (!destExists) {
    uint flag;
    const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
    const char* destName = destVec[destVec.size() - 1].c_str();
    uint iNode = sourceDir->iNumberOf((byte *) sourceFile);
    uint sourceType = sourceDir->fv->inodes.getType(iNode);
    if (sourceIsFile || sourceType == iTypeSoftLink) {
      flag = 0;
    }
    else {
      flag = 1;
      if (fileInPath(destVec, iNode)) {
        printf("Cannot move a directory into its own subdirectory.\n");
        return;
      }
    }
    sourceDir->deleteFile((byte *) sourceFile, 0);
    destDir->customCreateFile((byte *) destName, iNode, flag);
    if (sourceType == iTypeSoftLink) {
      destDir->fv->inodes.setType(iNode, iTypeSoftLink);
    }
    if (flag == 1) {
      Directory* newDir = new Directory(fv, iNode, 0);
      newDir->customDeleteFile((byte *) "..", 0);
      uint destINode = destDir->iNumberOf((byte *) ".");
      newDir->customCreateFile((byte *) "..", destINode, flag);
      if (newDir != wd) {
        delete(newDir);
      }
    }
    printf("Renamed successfully.\n");
  }
  else if (destExists) {
    uint flag;
    const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
    const char* destName = destVec[destVec.size() - 1].c_str();
    uint iNode = sourceDir->iNumberOf((byte *) sourceFile);
    uint destINode = destDir->iNumberOf((byte *) destName);
    if (destDir->fv->inodes.getType(destINode) == iTypeDirectory) {
      Directory* tmp = destDir;
      destDir = new Directory(fv, destINode, 0);
      if (tmp != wd) {
        delete(tmp);
      }
      delete(startDir);
    }
    else if (destDir->fv->inodes.getType(destINode) == iTypeSoftLink) {
      uint bn = fv->inodes.getBlockNumber(destINode, 0);
      byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
      fv->readBlock(bn, blockData);
      if (blockData[1] == '.') {
        blockData+=2;
      }
      bool success = successiveCD((char*) blockData);
      destDir = wd;
      wd = startDir;
      if (!success) {
        printf("Move failed.\n");
        return;
      }
    }
    if (destDir->iNumberOf((byte *) sourceFile) != 0) {
      if (destDir != wd) {
        delete(destDir);
      }
      printf("File/Directory already exists.\n");
      return;  
    }
    uint sourceType = sourceDir->fv->inodes.getType(iNode);
    if (sourceIsFile || sourceType == iTypeSoftLink) {
      flag = 0;
    }
    else {
      flag = 1;
      if (fileInPath(destVec, iNode)) {
        if (destDir != wd) {
          delete(destDir);
        }
        printf("Cannot move a directory into its own subdirectory.\n");
        return;
      }
    }
    sourceDir->deleteFile((byte *) sourceFile, 0);
    destDir->customCreateFile((byte *) sourceFile, iNode, flag);
    if (sourceType == iTypeSoftLink) {
      destDir->fv->inodes.setType(iNode, iTypeSoftLink);
    }
    if (flag == 1) {
      Directory* newDir = new Directory(fv, iNode, 0);
      newDir->customDeleteFile((byte *) "..", 0);
      newDir->customCreateFile((byte *) "..", destINode, flag);
      if (newDir != wd) {
        delete(newDir);
      }
    }
    printf("Moved successfully.\n");
  }

  if (sourceDir != wd) {
    delete(sourceDir);
  }
  if (destDir != wd) {
    delete(destDir);
  }
}

void doHardLink(Arg * a)
{
  Directory * startDir = new Directory(fv, wd->nInode, 0);
  bool sourceInvalidPath = false;
  bool sourceIsFile = false;
  bool sourceExists = true;
  bool destInvalidPath = false;
  bool destIsFile = false;
  bool destExists = true;

  // https://stackoverflow.com/questions/16515582/how-to-perform-a-deep-copy-of-a-char and 
  // https://stackoverflow.com/questions/481673/make-a-copy-of-a-char
  char* destPath = new char[strlen(a[1].s)+1]; // allocate for string and ending \0
  strcpy(destPath, a[1].s);
  // end citation

  std::vector<std::string> sourceVec = doMvPath(a[0].s, sourceInvalidPath, sourceIsFile, sourceExists);
  Directory* sourceDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);

  std::vector<std::string> destVec = doMvPath(destPath, destInvalidPath, destIsFile, destExists);
  if (destVec.size() == 0) {
    destVec.push_back(".");
  }
  delete(destPath);
  Directory* destDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);

  const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
  uint iNode = sourceDir->iNumberOf((byte *) sourceFile);
  const char* destName = destVec[destVec.size() - 1].c_str();
  uint destINode = destDir->iNumberOf((byte *) destName);

  if (!sourceExists || sourceInvalidPath || sourceDir->fv->inodes.getType(iNode) == iTypeDirectory || destInvalidPath || (destExists && destIsFile)) {
    if (sourceDir != wd) {
      delete(sourceDir);
    }
    if (destDir != wd) {
      delete(destDir);
    }
    printf("Creation of hard link failed.\n");
    return;
  }
  else if (destExists && !destIsFile) {
    if (destDir->fv->inodes.getType(destINode) == iTypeDirectory) {
      Directory* tmp = destDir;
      destDir = new Directory(fv, destINode, 0);
      if (tmp != wd) {
        delete(tmp);
      }
    }
    else if (destDir->fv->inodes.getType(destINode) == iTypeSoftLink) {
      uint bn = fv->inodes.getBlockNumber(destINode, 0);
      byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
      fv->readBlock(bn, blockData);
      if (blockData[1] == '.') {
        blockData+=2;
      }
      std::string pathStr = (char *) blockData;
      uint destType = getLinkType(pathStr);
      if (destType == iTypeDirectory) {
        bool success = successiveCD((char *) blockData);
        destDir = wd;
        wd = startDir;
        if (!success) {
          printf("Creation of hard link failed.\n");
          return;
        }
      }
      else {
        wd = startDir;
        printf("Creation of hard link failed.\n");
        return;
      }
    }
    if (destDir->iNumberOf((byte *) sourceFile) == 0) {
      uint type = sourceDir->fv->inodes.getType(iNode);
      uint newINode = destDir->customCreateFile((byte *) sourceFile, iNode, 0);
      if (type == iTypeSoftLink) {
        destDir->fv->inodes.setType(newINode, iTypeSoftLink);
      }
      printf("Hard link with inode %d created successfully.\n", newINode);
      fv->inodes.incLinkCount(iNode, 1);
    }
    else {
      printf("File with name %s already exists in the destination directory.\n", sourceFile);
    }
  }
  else if (!destExists) {
    uint type = sourceDir->fv->inodes.getType(iNode);
    uint newINode = destDir->customCreateFile((byte *) destName, iNode, 0);
    if (type == iTypeSoftLink) {
      destDir->fv->inodes.setType(newINode, iTypeSoftLink);
    }
    printf("Hard link with inode %d created successfully.\n", newINode);
  }
  else {
    printf("Creation of hard link failed.\n");
  }

  if (sourceDir != wd) {
    delete(sourceDir);
  }
  if (destDir != wd) {
    delete(destDir);
  }
  wd = startDir;
}

void doHardLinkCurDir(Arg * a) {
  a[1].s = ".";
  doHardLink(a);
}

void doSoftLink(Arg * a) {
  if (strcmp(a[0].s, "-s") != 0) {
    printf("Incorrect flag for symbolic link creation.\n");
  }
  Directory * startDir = new Directory(fv, wd->nInode, 0);
  bool sourceInvalidPath = false;
  bool sourceIsFile = false;
  bool sourceExists = true;
  bool destInvalidPath = false;
  bool destIsFile = false;
  bool destExists = true;

  // https://stackoverflow.com/questions/16515582/how-to-perform-a-deep-copy-of-a-char and 
  // https://stackoverflow.com/questions/481673/make-a-copy-of-a-char
  char* destPath = new char[strlen(a[2].s)+1]; // allocate for string and ending \0
  strcpy(destPath, a[2].s);
  // end citation

  std::vector<std::string> sourceVec = doMvPath(a[1].s, sourceInvalidPath, sourceIsFile, sourceExists);
  Directory* sourceDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);

  std::vector<std::string> destVec = doMvPath(destPath, destInvalidPath, destIsFile, destExists);
  if (destVec.size() == 0) {
    destVec.push_back(".");
  }
  delete(destPath);
  Directory* destDir = new Directory(fv, wd->nInode, 0);
  delete(wd);
  wd = new Directory(fv, startDir->nInode, 0);
  
  const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
  const char* destName = destVec[destVec.size() - 1].c_str();
  uint destINode = destDir->iNumberOf((byte *) destName);

  if (!sourceExists || sourceInvalidPath || destInvalidPath || (destExists && destIsFile)) {
    if (sourceDir != wd) {
      delete(sourceDir);
    }
    if (destDir != wd) {
      delete(destDir);
    }
    printf("Creation of symbolic link failed.\n");
    return;
  }
  else if (destExists && !destIsFile) {
    if (destDir->fv->inodes.getType(destINode) == iTypeDirectory) {
      Directory* tmp = destDir;
      destDir = new Directory(fv, destINode, 0);
      if (tmp != wd) {
        delete(tmp);
      }
    }
    else if (destDir->fv->inodes.getType(destINode) == iTypeSoftLink) {
      uint bn = fv->inodes.getBlockNumber(destINode, 0);
      byte *blockData = new byte[fv->superBlock.nBytesPerBlock];
      fv->readBlock(bn, blockData);
      if (blockData[1] == '.') {
        blockData+=2;
      }
      std::string pathStr = (char *) blockData;
      uint destType = getLinkType(pathStr);
      if (destType == iTypeDirectory) {
        bool success = successiveCD((char *) blockData);
        destDir = wd;
        wd = startDir;
        if (!success) {
          printf("Creation of symbolic link failed.\n");
          return;
        }
      }
      else {
        wd = startDir;
        printf("Creation of symbolic link failed.\n");
        return;
      }
    }
    if (destDir->iNumberOf((byte *) sourceFile) == 0) {
      std::string sourceAbsPath = getAbsPath(sourceDir);
      sourceAbsPath = sourceAbsPath + "/" + sourceVec[sourceVec.size() - 1];
      const char* sourcePathPointer = sourceAbsPath.c_str();
      uint linkINode = destDir->createFile((byte *) sourceFile, 0);
      destDir->fv->inodes.setType(linkINode, iTypeSoftLink);
      File* pathFile = new File(fv, linkINode);
      sourceDir = new Directory(fv, sourceDir->nInode, 0);
      pathFile->appendBytes((byte *) sourcePathPointer, strlen(sourcePathPointer) + strlen(sourceFile));
      delete pathFile;
      printf("Symbolic link with inode %d created successfully.\n", linkINode);
    }
    else {
      printf("File or directory with name %s already exists in the destination directory.\n", sourceFile);
    }
  }
  else if (!destExists) {
    std::string sourceAbsPath = getAbsPath(sourceDir);
    sourceAbsPath = sourceAbsPath + "/" + sourceVec[sourceVec.size() - 1];
    const char *sourcePathPointer = sourceAbsPath.c_str();
    uint linkINode = destDir->createFile((byte *)destName, 0);
    fv->inodes.setType(linkINode, iTypeSoftLink);
    File *pathFile = new File(fv, linkINode);
    sourceDir = new Directory(fv, sourceDir->nInode, 0);
    pathFile->appendOneBlock((byte *)sourcePathPointer, strlen(sourcePathPointer) + strlen(destName)); // only has . here
    delete pathFile;
    printf("Symbolic link with inode %d created successfully.\n", linkINode);
  }
  else
  {
    printf("Creation of symbolic link failed.\n");
  }

  if (sourceDir != wd && sourceDir != NULL) {
    delete(sourceDir);
  }
  if (destDir != wd && destDir != NULL) {
    delete(destDir);
  }
}

void doMountDF(Arg * a)   // arg a ignored
{
  TODO("doMountDF");
}

void doMountUS(Arg * a)
{
  TODO("doMountUS");
}

void doUmount(Arg * a)
{
  TODO("doUmount");
}

/* The following describes one entry in our table of commands.  For
 * each cmmdName (a null terminated string), we specify the arguments
 * it requires by a sequence of letters.  The letter s stands for
 * "that argument should be a string", the letter u stands for "that
 * argument should be an unsigned int."  The data member (func) is a
 * pointer to the function in our code that implements that command.
 * globalsNeeded identifies whether we need a volume ("v"), a simdisk
 * ("d"), or a mount table ("m").  See invokeCmd() below for exact
 * details of how all these flags are interpreted.
 */

class CmdTable {
public:
  char *cmdName;
  char *argsRequired;
  char *globalsNeeded;    // need d==simDisk, v==cfv, m=mtab
  void (*func) (Arg * a);
} cmdTable[] = {
    {"cd", "s", "v", doChDir},
    {"cp", "ss", "v", doCopy},
    {"echo", "ssss", "", doEcho},
    {"inode", "u", "v", doInode},
    {"inode", "s", "v", doInodeName},
    {"ls", "", "v", doLsLong},
    {"lslong", "", "v", doLsLong},
    {"ls", "s", "v", doLsName},
    {"ls", "ss", "v", doLsNameRecursive},
    {"mkdir", "s", "v", doMkDir},
    {"touch", "s", "v", doTouch},
    {"mkdisk", "s", "", doMakeDisk},
    {"mkfs", "s", "", doMakeFV},
    {"mount", "us", "", doMountUS},
    {"mount", "", "", doMountDF},
    {"mv", "ss", "v", doMv},
    {"rddisk", "su", "", doReadDisk},
    {"rmdir", "s", "v", doRm},
    {"rm", "s", "v", doRm},
    {"rm", "ss", "v", doRmRecursive},
    {"pwd", "", "v", doPwd},
    {"q", "", "", doQuit},
    {"quit", "", "", doQuit},
    {"umount", "u", "m", doUmount},
    {"wrdisk", "sus", "", doWriteDisk},
    {"ln", "ss", "v", doHardLink},
    {"ln", "s", "v", doHardLinkCurDir},
    {"ln", "sss", "v", doSoftLink}
};

uint ncmds = sizeof(cmdTable) / sizeof(CmdTable);

void usage()
{
  printf("The shell has only the following cmds:\n");
  for (uint i = 0; i < ncmds; i++)
    printf("\t%s\t%s\n", cmdTable[i].cmdName, cmdTable[i].argsRequired);
  printf("Start with ! to invoke a Unix shell cmd\n");
}

/* pre:: k >= 0, arg[] are set already;; post:: Check that args are
 * ok, and the needed simDisk or cfv exists before invoking the
 * appropriate action. */

void invokeCmd(int k, Arg *arg)
{
  uint ok = 1;
  if (cmdTable[k].globalsNeeded[0] == 'v' && cwdVNIN == 0) {
    ok = 0;
    printf("Cmd %s needs the cfv to be != 0.\n", cmdTable[k].cmdName);
  }
  else if (cmdTable[k].globalsNeeded[0] == 'm' && mtab == 0) {
    ok = 0;
    printf("Cmd %s needs the mtab to be != 0.\n", cmdTable[k].cmdName);
  }

  char *req = cmdTable[k].argsRequired;
  uint na = strlen(req);
  for (uint i = 0; i < na; i++) {
    if (req[i] == 's' && (arg[i].s == 0 || arg[i].s[0] == 0)) {
      ok = 0;
      printf("arg #%d must be a non-empty string.\n", i);
    }
    if ((req[i] == 'u') && (arg[i].s == 0 || !isDigit(arg[i].s[0]))) {
      ok = 0;
      printf("arg #%d (%s) must be a number.\n", i, arg[i].s);
    }
  }
  if (ok)
    (*cmdTable[k].func) (arg);
}

/* pre:: buf[] is the command line as typed by the user, nMax + 1 ==
 * sizeof(types);; post:: Parse the line, and set types[], arg[].s and
 * arg[].u fields.
 */

void setArgsGiven(char *buf, Arg *arg, char *types, uint nMax)
{
  for (uint i = 0; i < nMax; i++) {
    arg[i].s = 0;
    types[i] = 0;
  }
  types[nMax] = 0;

  strtok(buf, " \t\n");   // terminates the cmd name with a \0

  for (uint i = 0; i < nMax;) {
    char *q = strtok(0, " \t");
    if (q == 0 || *q == 0) break;
    arg[i].s = q;
    arg[i].u = toNum(q);
      types[i] = isDigit(*q)? 'u' : 's';
    nArgs = ++i;
  }
}

/* pre:: name pts to the command token, argtypes[] is a string of
 * 's'/'u' indicating the types of arguments the user gave;; post::
 * Find the row number of the (possibly overloaded) cmd given in
 * name[].  Return this number if found; return -1 otherwise. */

int findCmd(char *name, char *argtypes)
{
  for (uint i = 0; i < ncmds; i++) {
    if (strcmp(name, cmdTable[i].cmdName) == 0
  && strcmp(argtypes, cmdTable[i].argsRequired) == 0) {
      return i;
    }
  }
  return -1;
}

void ourgets(char *buf) {
  fgets(buf, 1024, stdin);
  char * p = index(buf, '\n');
  if (p) *p = 0;
}

int main()
{
  char buf[1024];   // better not type longer than 1023 chars

  usage();
  for (;;) {
    *buf = 0;     // clear old input
    printf("%s", "sh33% "); // prompt
    ourgets(buf);
    printf("cmd [%s]\n", buf);  // just print out what we got as-is
    if (buf[0] == 0)
      continue;
    if (buf[0] == '#')
      continue;     // this is a comment line, do nothing
    if (buf[0] == '!')    // begins with !, execute it as
      system(buf + 1);    // a normal shell cmd
    else {
      setArgsGiven(buf, arg, types, nArgsMax);
      int k = findCmd(buf, types);
      if (k >= 0)
        invokeCmd(k, arg);
      else
        usage();
    }
  }
}

// -eof-
