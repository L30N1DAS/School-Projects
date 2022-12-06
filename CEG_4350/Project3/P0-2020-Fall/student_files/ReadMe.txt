Note: Indirection (Medium or Large files) was not completed for this project.

(i)
Anmol Saini
saini.25@wright.edu

(ii)
P0-2020-Fall
-rw------- 1 anmolsaini anmolsaini  2902 Apr  2  2007 bitvector.cpp
-rw------- 1 anmolsaini anmolsaini  6950 Dec  4 05:41 directory.cpp
-rw------- 1 anmolsaini anmolsaini   174 Apr  2  2007 diskParams.dat
-rw------- 1 anmolsaini anmolsaini  4199 Dec  2 01:37 file.cpp
-rw------- 1 anmolsaini anmolsaini  7312 Nov 23 19:01 fs33types.hpp
-rw------- 1 anmolsaini anmolsaini  8323 Dec  2 23:26 inodes.cpp
-rw------- 1 anmolsaini anmolsaini   722 Jul  7  2020 Makefile
-rw------- 1 anmolsaini anmolsaini  3641 Apr  2  2007 mount.cpp
-rw------- 1 anmolsaini anmolsaini 40012 Dec  6 06:06 shell.cpp
-rw------- 1 anmolsaini anmolsaini  3780 Apr  2  2007 simdisk.cpp
drwxrwxr-x 2 anmolsaini anmolsaini  4096 Dec  6 16:58 student_files
-rw-r--r-- 1 anmolsaini anmolsaini  2718 Sep 24  2020 typescript
-rw------- 1 anmolsaini anmolsaini   112 Apr  2  2007 user.cpp
-rw------- 1 anmolsaini anmolsaini  7747 Dec  3 20:30 volume.cpp

student_files
-rw-rw-r-- 1 anmolsaini anmolsaini 2741 Dec  6 17:42 ReadMe.txt
-rw-rw-r-- 1 anmolsaini anmolsaini  780 Dec  5 20:44 testscript.txt

(iii)
The files in this directory's parent constitute a simple implementation of a file system written in C++. This project
primarily focused on modifying shell.cpp to enhance funtionality. For this project, functionality for hard links and soft links
was to be implemented. The structure of my project entails indefinitely requesting input from the user using a simulated shell
prompt and executing the command if it is found in a command table with appropriate arguments. For the most part, these shell
commands are relatively independent of each other. A few of them might invoke the same functions to achieve a similar outcome
or even each other in some cases however. ln creates hard links (i.e., a duplicate of the provided file/symbolic link
with the same inode and given name, if one is given, at the provided destination). ln -s creates symbolic links (i.e., a new file
that stores the path of and references the source file with the given name, if one is given, at the provided destination).

(iv)
ln
Pros: My implementation for ln creates hard links in a fashion very similar to Linux. cd, mv, cp, ls, and rm all work as expected
    for hard links.
Cons: My implementation for ln is somewhat convoluted and unorthodox due to using vectors.
ln -s
Pros: My implementation for ln -s creates symbolic links in a fashion very similar to Linux. cd, mv, cp, ls, and rm all works as
    expected for symbolic links.
Cons: My implementation for ln -s is somewhat convoluted and unorthodox due to using vectors.
Indirection (Incomplete)
