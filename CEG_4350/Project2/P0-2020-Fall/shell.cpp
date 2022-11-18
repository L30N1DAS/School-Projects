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
  // public funct: nameOf()
  // printf("%s", );
  // wd->nInode; current dir's inode

  // uint parentINode = wd->iNumberOf((byte *) "..");
  // Directory* parentDir = new Directory(fv, parentINode, 0);
  // printf("%s\n", (char *) parentDir->nameOf(wd->nInode));

  Directory* curDir = wd;
  Directory* parentDir;
  uint parentINode = 0;
  std::vector<std::string> pathVec;
  std::string path = "";

  while (parentINode != 1) {
    parentINode = curDir->iNumberOf((byte *) "..");
    // if (parentDir != NULL) {
    //   delete(parentDir);
    // }
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

  // printf("%s\n", path);
  std::cout << path << std::endl;
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
    //std::cout << a[0].s << std::endl;
  }
}

void doLsNameRecursiveHelper(const char * name) {
  uint iNode = wd->iNumberOf((byte *) name);
  if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
    wd = new Directory(fv, iNode, 0);
    // printf("%s\n", name);
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
  //wd = curDir;
}

void doLsNameRecursive(Arg * a) {
  if (strcmp(a[0].s, "-lR") != 0) {
    printf("Incorrect flag for recursive ls");
    return;
  }
  Directory * curDir = wd;
  doLsNameRecursiveHelper(a[1].s);
  wd = curDir;
}

uint getNumDirs(uint iNode) {
  Directory * targetDir = new Directory(fv, iNode, 0);
  std::vector<std::string> entriesVec = targetDir->getEntries();
  uint numDirs = 0;
  for (long unsigned int i = 0; i < entriesVec.size(); i++) {
    const char * vecEntry = entriesVec[i].c_str();
    iNode = targetDir->iNumberOf((byte *) vecEntry);
    if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
      numDirs++;
    }
  }
  return numDirs;
}

void doRm(Arg * a)
{
  // uint in = wd->fv->deleteFile((byte *) a[0].s);
  uint in = wd->iNumberOf((byte *) a[0].s);
  if (in == 0) {
    printf("File/Directory not found.\n");
    return;
  }
  uint numContents = 0;
  uint numDirs = 0;
  if (wd->fv->inodes.getType(in) == iTypeDirectory) {
    numContents = wd->lsInvis(in);
    numDirs = getNumDirs(in);
  }
  if (wd->fv->inodes.getType(in) == iTypeOrdinary || (wd->fv->inodes.getType(in) == iTypeDirectory && numContents == 0)) {
    in = wd->deleteFile((byte *) a[0].s, 1);
    printf("rm %s (contains %d directories) returns %d.\n", a[0].s, numDirs, in); // probably shouldn't say contains x dirs if a file
    return;
  }
  printf("Removal failed.\n");
  printf("%s contains %d directories.\n", a[0].s, numDirs);
}

void doRmRecursiveHelper(const char * name) {
  uint iNode = wd->iNumberOf((byte *) name);
  if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
    wd = new Directory(fv, iNode, 0);
    // printf("%s\n", name);
    // doLsLong((Arg *) name);
  }
  else if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeOrdinary) {
    //wd->deleteFile((byte *) name, 1);
    // printf("%7d %crw-rw-rw-    1 yourName yourGroup %7d Jul 15 12:34 %s\n",
	  //    iNode, '-', wd->fv->inodes.getFileSize(iNode), name);
    return;
  }
  else if (iNode == 0) {
    printf("File/Directory not found.\n"); // check what happens for `rm -fr .`; might just delete .; nvm, iNode = 1 for .
    return;
  }
  Directory * curDir = wd;
  std::vector<std::string> entriesVec = wd->getEntries();
  for (long unsigned int i = 0; i < entriesVec.size(); i++) {
    const char * vecEntry = entriesVec[i].c_str();
    iNode = wd->iNumberOf((byte *) vecEntry);
    if (iNode != 0 /*&& wd->fv->inodes.getType(iNode) == iTypeDirectory*/) {
      doRmRecursiveHelper(vecEntry);
      wd = curDir;
      wd->deleteFile((byte *) vecEntry, 1);
      // wd = curDir;
    }
  }
  delete(wd);
  //wd = curDir;
}

void doRmRecursive(Arg * a) {
  if (strcmp(a[0].s, "-fr") != 0) {
    printf("Incorrect flag for recursive rm.\n");
    return;
  }
  Directory * curDir = wd;
  doRmRecursiveHelper(a[1].s);
  wd = curDir;
  wd->deleteFile((byte *) a[1].s, 1);
}

void doInode(Arg * a)
{
  uint ni = a[0].u;

  wd->fv->inodes.show(ni);
}

void doInodeName(Arg * a)
{
  uint iNode = wd->iNumberOf((byte *) a[0].s);
  // doInode((Arg*) iNode);
  // uint ni = a[0].u;
  wd->fv->inodes.show(iNode);
}

void doMkDir(Arg * a)
{
  uint in = wd->createFile((byte *) a[0].s, 1); // iTypeDirectory
  printf("inode: %d\n", in);
  // Directory* newDir = new Directory(fv, fv->inodes.getFree(), wd->iNumberOf()); // how to access iNumberOf in Dir class
}

void doTouch(Arg * a) {
  uint in = wd->createFile((byte *) a[0].s, 0);
  printf("inode: %d\n", in);
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

std::string getRemPathStr(char* remPathChar) {
  bool startSpace = false;
  std::string remPathStr;

  while (remPathChar != 0) {
    if (startSpace) {
      remPathStr = remPathStr + " ";
    }
    for (long unsigned int i = 0; i < strlen(remPathChar); i++) {
      remPathStr = remPathStr + remPathChar[i];
    }
    remPathChar = strtok(0, " \t");
    startSpace = true;
  }
  return remPathStr;
}

void updatePath(char* path, std::string newPath) {
  for (long unsigned int i = 0; i < newPath.length(); i++) {
    path[i] = newPath[i];
  }
  path[newPath.length()] = '\0';
}

bool fixPath (char* path) {
  // int len = strlen(path);
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
  // char *ogPath = new char(*path);
  std::vector<std::string> pathVec;
  if (!fixPath(path)) {
    //printf("Changing directory failed\n");
    return pathVec;
  }
  std::string remPathStr;
  if (path[0] != '/') {
    remPathStr = path;
    remPathStr = "/" + remPathStr;
    updatePath(path, remPathStr);
  }
  uint numSlashes = findNumSlashes(path);
  // std::vector<std::string> pathVec;
  for (uint i = 0; i < numSlashes; i++) {
    // pathVec[i] = strtok(path, "/");
    pathVec.push_back(strtok(path, "/"));
    char* remPathChar = strtok(0, " \t");
    // std::string remPathStr = getRemPathStr(remPathChar);
    if (remPathChar == 0 && i == numSlashes - 1) {
      break;
    }
    remPathStr = remPathChar;
    // if ((remPathChar == "" || remPathChar == "/") && i != numSlashes) {
    //   printf("Invalid path.\n");
    //   // failedPath = true;
    //   break;
    // }
    // std::string remPathStr = remPathChar;
    // pathVec[i] = remPathStr;
    // pathVec.push_back(remPathStr);
    remPathStr = "/" + remPathStr;
    updatePath(path, remPathStr);
  }
  // path = ogPath;
  // delete ogPath;
  return pathVec;
}

void doChDir(Arg * a)
{
  bool toRoot;
  bool afterRoot = true;
  Directory* startDir = wd;
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
    // uint numSlashes = findNumSlashes[a[0].s];
    // std::string path[];
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
      // char pathEntry[pathVec[i].length()];
      // pathEntry[0] = pathVec[i];
      iNode = wd->iNumberOf((byte *) pathEntry);
      if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
        Directory* tmp = wd;
        wd = new Directory(fv, iNode, 0);
        if (tmp != startDir) {
          delete(tmp);
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
  printf("\n");

  // else {
  //   uint iNode = wd->iNumberOf((byte *) a[0].s);
  //   if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
  //     wd = new Directory(fv, iNode, 0);
  //   }
  //   else {
  //     printf("Changing directory failed\n");
  //   }
  //   doPwd(a);
  // }
}

std::vector<std::string> doMvPath(char * path, bool& invalidPath, bool& IsFile, bool& exists)
{
  bool toRoot;
  bool afterRoot = true;
  Directory* startDir = wd;
  if (path[0] == '/') {
    toRoot = true;
    if (path[1] == 0) {
      afterRoot = false;
      // printf("Changing directory to root\n");
    }
    else if (path[1] == '/') {
      afterRoot = false;
      for (long unsigned int i = 0; i < strlen(path); i++) {
        if (path[i] != '/') {
          toRoot = false;
          //printf("Changing directory failed\n");
          break;
        }
        else {
          toRoot = true;
        }
      }
      // if (toRoot) {
      //   printf("Changing directory to root\n");
      // }
    }
  }
  if (toRoot) {
    // uint numSlashes = findNumSlashes[a[0].s];
    // std::string path[];
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
      // char pathEntry[pathVec[i].length()];
      // pathEntry[0] = pathVec[i];
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
        //wd = new File(fv, iNode);
        IsFile = true;
        break;
      }
      else if (iNode == 0 && i == pathVec.size() - 1) {
        exists = false;
      }
      else {
        // printf("Changing directory failed\n");
        // wd = startDir;
        invalidPath = true;
        break;
      }
    }
    if (pathVec.size() == 0) {
      // wd = startDir;
      // invalid Path
      invalidPath = true;
    }
  }
  //doPwd((Arg *) path);

  // else {
  //   uint iNode = wd->iNumberOf((byte *) a[0].s);
  //   if (iNode != 0 && wd->fv->inodes.getType(iNode) == iTypeDirectory) {
  //     wd = new Directory(fv, iNode, 0);
  //   }
  //   else {
  //     printf("Changing directory failed\n");
  //   }
  //   doPwd(a);
  // }

  // if (wd != startDir) {
  //   delete(startDir);
  // }
  return pathVec;
}

void doMv(Arg * a)
{
  //TODO("doMv");
  Directory * startDir = wd;
  bool sourceInvalidPath = false;
  bool sourceIsFile = false;
  bool sourceExists = true;
  bool destInvalidPath = false;
  bool destIsFile = false;
  bool destExists = true;

  // size_t len = strlen(a[1].s)+1;
  char* destPath = new char[strlen(a[1].s)+1]; // allocate for string and ending \0
  strcpy(destPath, a[1].s);

  // char * copy = malloc(strlen(a[1].s) + 1); 
  // strcpy(copy, a[1].s);

  std::vector<std::string> sourceVec = doMvPath(a[0].s, sourceInvalidPath, sourceIsFile, sourceExists);
  // if (invalidPath) {
  //   printf("Invalid args.\n");
  //   return;
  // }
  Directory* sourceDir = wd;
  wd = startDir;
  std::vector<std::string> destVec = doMvPath(destPath, destInvalidPath, destIsFile, destExists);
  delete(destPath);
  // if (invalidPath) {
  //   printf("Invalid args.\n");
  //   return;
  // }
  Directory* destDir = wd;
  wd = startDir;

  if (!sourceExists || sourceInvalidPath || destInvalidPath || (destExists && destIsFile)) {
    // return 0;
    printf("Move/Rename failed.\n");
    return;
  }
  else if (!destExists) {
    //if (sourceIsFile) {
    uint flag;
    const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
    // if (destDir->iNumberOf((byte *) sourceFile) != 0) {
    //   return;
    // }
    const char* destName = destVec[destVec.size() - 1].c_str();
    if (sourceIsFile) {
      flag = 0;
    }
    else {
      flag = 1;
    }
    uint iNode = sourceDir->deleteFile((byte *) sourceFile, 0);
    destDir->customCreateFile((byte *) destName, iNode, flag);
    printf("Renamed successfully.\n");
    //}
  }
  else if (destExists) {
    //if (sourceIsFile) {
    uint flag;
    const char* sourceFile = sourceVec[sourceVec.size() - 1].c_str();
    const char* destName = destVec[destVec.size() - 1].c_str();
    uint destINode = destDir->iNumberOf((byte *) destName);
    destDir = new Directory(fv, destINode, 0);
    if (destDir->iNumberOf((byte *) sourceFile) != 0) {
      return;
    }
    if (sourceIsFile) {
      flag = 0;
    }
    else {
      flag = 1;
    }
    uint iNode = sourceDir->deleteFile((byte *) sourceFile, 0);
    destDir->customCreateFile((byte *) sourceFile, iNode, flag);
    printf("Moved successfully.\n");
    //}
  }

  if (sourceDir != wd) {
    delete(sourceDir);
  }
  if (destDir != wd) {
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
    {"wrdisk", "sus", "", doWriteDisk}
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

// what happens for rm .
// how to return 0
// should rm print all entries or only entries that are directories
// penalty for memory leaks