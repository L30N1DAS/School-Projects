(i)
Anmol Saini
saini.25@wright.edu

(ii)
P0-2020-Fall
-rw------- 1 anmolsaini anmolsaini  2902 Apr  2  2007 bitvector.cpp
-rw------- 1 anmolsaini anmolsaini  6344 Nov 18 16:19 directory.cpp
-rw------- 1 anmolsaini anmolsaini   174 Apr  2  2007 diskParams.dat
-rw------- 1 anmolsaini anmolsaini  4199 Apr  2  2007 file.cpp
-rw------- 1 anmolsaini anmolsaini  7243 Nov 18 16:20 fs33types.hpp
-rw------- 1 anmolsaini anmolsaini  7569 Apr  2  2007 inodes.cpp
-rw------- 1 anmolsaini anmolsaini   722 Jul  7  2020 Makefile
-rw------- 1 anmolsaini anmolsaini  3641 Apr  2  2007 mount.cpp
-rw------- 1 anmolsaini anmolsaini 23390 Nov 18 21:50 shell.cpp
-rw------- 1 anmolsaini anmolsaini  3780 Apr  2  2007 simdisk.cpp
drwxrwxr-x 2 anmolsaini anmolsaini  4096 Nov 18 22:32 student_files
-rw-r--r-- 1 anmolsaini anmolsaini  2718 Sep 24  2020 typescript
-rw------- 1 anmolsaini anmolsaini   112 Apr  2  2007 user.cpp
-rw------- 1 anmolsaini anmolsaini  7280 Nov 16 13:20 volume.cpp

student_files
-rw-rw-r-- 1 anmolsaini anmolsaini 3368 Nov  2 11:34 answers.txt
-rw-rw-r-- 1 anmolsaini anmolsaini 9878 Nov  3 07:56 gdbSession.txt
-rw-rw-r-- 1 anmolsaini anmolsaini  624 Nov 18 12:24 improvements.txt
-rw-rw-r-- 1 anmolsaini anmolsaini 1052 Nov 18 22:37 ReadMe.txt
-rw-rw-r-- 1 anmolsaini anmolsaini  559 Nov 18 22:27 testscript.txt

(iii)
The files in this directory's parent constitute a simple implementation of a file system written in C++. This project
primarily focused on modifying shell.cpp to enhance funtionality (and partly fs33types.hpp to #include more files and
directory.cpp to enable the enhancements). For this project, functionality for mkdir, cd, rm, ls, pwd, inode, and mv was to be
implemented. The structure of my project entails indefinitely requesting input from the user using a simulated shell prompt
and executing the command if it is found in a command table with appropriate arguments. For the most part, these shell
commands are relatively independent of each other. A few of them might invoke the same functions to achieve a similar outcome
or even each other in some cases however. mkdir creates a new file, assigning it a directory flag. Similarly, although not
required by the project, I implemented touch. Like mkdir, it creates a new file but with a different flag. rm deletes any file
and any directory if it is empty. ls prints the contents of a directory or information about a file as it would appear if it
were a directory entry. pwd prints the absolute path of the working directory. inode prints information about a file or
directory if given either an inode or a name. mv moves a file or directory into a directory and can also rename a file or
directory.

(iv)
mkdir
Pros: My implementation for mkdir is short and simple and clearly states whether a directory is created or not.
Cons: My implementation for mkdir is not compatible with paths. As such, it can be inconvenient to cd to a location before
    being able to create a directory.
cd
Pros: My implementation for cd is compatible with both relative and absolute paths, as well as with just a single directory
    name. It is fairly robust as well, accounting for and eliminating any number of slashes that may occur at the beginning
    or end of a path. It also distinguishes directories from files and avoids memory leaks.
Cons: My implementation for cd is fairly complex, as it must determine whether a path is being provided or simply a directory
    name. It must also parse a path if one is given. My implementation also uses a vector of strings to store the entries in
    a path to make the implementation easier but potentially less efficient.
rm
Pros: My implementation for rm is simple and clearly lays out different mutually exclusive scenarios, accounting for all of them.
    It is fairly robust, checking whether a file or directory is to be deleted, and ensuring any directory to be deleted is
    empty. In addition, I have implemented a recursive option that deletes a directory along with all the contents of its
    subdirectories. My implementation avoids memory leaks.
Cons: My implementation for rm is not compatible with paths. As such, it can be inconvenient to cd to a location before
    being able to remove a directory or file.
ls
Pros: My implementation for ls is simple and displays the output in a neatly formatted manner. It distinguishes directories
    from files and avoids memory leaks. An option has also been implemented to recursively displays the contents of a directory
    and its subdirectories. This options avoids memory leaks as well.
Cons: My implementation for ls is not compatible with paths. As such, it can be inconvenient to cd to a location before
    being able to view the contents of a directory.
pwd
Pros: My implementation for pwd is simple and successfully displays the absolute path of the current working directory while
    avoiding memory leaks.
Cons: My implementation for pwd had trouble printing out the path with printf. As such, I decided to use cout. Although this
    solution does work, I had to #include some libraries that I otherwise would not have had to, making the code somewhat
    less efficient.
inode
Pros: My implementation for inode is simple and successfully displays information associated with an inode given the inode
    or the name of the file or directory to which that inode belongs.
Cons: My implementation for inode prints the contents of an empty inode if it cannot be found rather than explicitly saying so.
mv
Pros: My implementation for mv takes several potential scenarios into account, determining whether a move or rename is to be
    done or potentially both. It is also compatible with absolute as well as relative paths
Cons: My implementation for mv is rather complex. While robust in the sense that it does not cause errors, my implementation
    does not always work as it should (according to how mv works in Linux). Given more time, I would have liked to continue
    working on mv.
