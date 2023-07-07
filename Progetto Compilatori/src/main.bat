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
gcc ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h -o main.exe

ECHO:
main.exe ./input/input1.txt
del main.exe ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h