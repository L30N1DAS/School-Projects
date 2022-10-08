(i)
CEG 4350 P0 ReadMe.txt
Anmol Saini
saini.25@wright.edu

(ii)
-rw-rw-r-- 1 anmolsaini anmolsaini  2902 Sep 21 03:16 bitvector.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini  5352 Sep 21 03:16 directory.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini   174 Sep 21 03:16 diskParams.dat
-rw-rw-r-- 1 anmolsaini anmolsaini  4199 Sep 21 03:16 file.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini  7040 Oct  2 06:45 fs33types.hpp
-rw-rw-r-- 1 anmolsaini anmolsaini  7569 Sep 21 03:16 inodes.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini   722 Sep 21 03:16 Makefile
-rw-rw-r-- 1 anmolsaini anmolsaini  3641 Sep 21 03:16 mount.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini 15108 Oct  7 06:30 shell.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini  3780 Sep 21 03:16 simdisk.cpp
drwxrwxr-x 2 anmolsaini anmolsaini  4096 Oct  4 15:29 student_files
-rw-rw-r-- 1 anmolsaini anmolsaini  2718 Sep 21 03:16 typescript
-rw-rw-r-- 1 anmolsaini anmolsaini   112 Sep 21 03:16 user.cpp
-rw-rw-r-- 1 anmolsaini anmolsaini  6808 Sep 21 03:16 volume.cpp

(iii)
The files in this directory's parent constitute a simple implementation of a file system written in C++. This project
primarily focused on modifying shell.cpp to enhance funtionality (and partly fs33types.hpp to #include more files). In
particular, three operators were implemented: > (redirection), & (background execution), and | (piping). The structure of
my project entails indefinitely requesting input from the user using a simulated shell prompt and executing the command if
it is found in a command table with appropriate arguments. For the implementation of redirection, background execution, and
piping, I used conditional statements to detect these symbols in the buffer and to potentially execute their functionality
if found before setting the arguments of commands. By doing so, I did not have to modify any of the provided functions
besides main(), making the overall implementation simpler as a result. Since other symbols were already being detected and
providing special functionality in the base project, however, the order of symbol detection in my project is extremely
important and had to be altered in some cases. The 0 and # symbols are detected first, as nothing is to be done if either is
found, followed by the & operator, as any of the other symbols below can and should be capable of background execution,
followed by the | operator, as a piped command can consist of redirection or a system command, followed by the > operator,
as output from a system command can still be redirected, finally followed by the ! operator, as it does not rely on any of
the above operators.

(iv)
Redirection
Pros: My implementation for redirection is quite short and simple. It also prevents errors that would be caused by cases
    such as "ls >" and "> ls", as well as abnormal spacing.
Cons: My implementation for redirection does not account for multiple > symbols. As such, it is possible to have a file
    named ">" or a file with a > in the name.
Piping
Pros: My implementation for piping is quite error-proof, as several scenarios noted in testscript.txt will not
    break my program, such as "ls |", "| !grep D1", "ls | | !grep D1", and "ls !grep D1 | |", as well abnormal spacing. In
    addition, it handles single and double piping successfully while noting its inability to run commands with three or
    more pipes instead of crashing if such a command is input.
Cons: My implementation for piping could be more efficient. It requires updating buf often one character at a time, and it
    requires two completely separate functions for single and double piping. In addition, my implementation stores the
    individual commands separated by pipes in a variable length array (which is used to update buf) instead of manipulating
    buf directly. It also does not allow for true multiple piping (three or more commands).
Background execution
Pros: My implementation for background execution is quite short and simple. It also prevents errors due to cases that should
    not be allowed based on the placement of &, such as "& ls > test" and "echo & this that these those". It also functions
    similarly to a Linux shell by executing everything up until the & as a background process if text does follow the & (i.e.
    ls & > test).
Cons: My implementation for background execution results in the background process becoming a defunct process despite exiting,
    as can be seen when "!ps" is run in testscript.txt.