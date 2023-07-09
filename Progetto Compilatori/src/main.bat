ECHO OFF

ECHO:

ECHO Compiling flex script...
cd ./flex
win_flex.exe LessicalParser.fl

cd ../

ECHO Compiling bison script...
cd ./bison
win_bison.exe SintaticsParser.y -d

cd ../

ECHO Compiling all files...
gcc -march=native -Ofast -flto -Wfatal-errors -Wall -Wextra -pedantic ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h ./symbol_table/hashtable.c -o main.exe

ECHO:
main.exe ./input/input.txt ./output/output.log
main.exe ./input/input2.txt ./output/output2.log
del main.exe flex\LessicalParser.c bison\SintaticsParser.tab.c bison\SintaticsParser.tab.h