ECHO OFF

ECHO Compiling flex script...
cd ./flex
win_flex.exe LessicalParser.fl

ECHO Compiling yy file...
gcc LessicalParser.c -o ../main.exe
del LessicalParser.c
cd ../

ECHO Scanning of input...
main.exe ./input/input1.txt ./output/output1.log


