ECHO OFF

ECHO:
ECHO ----------------------------------------------------------------------------------------------------------

ECHO Compiling flex script...
cd ./flex
win_flex.exe LessicalParser.fl

cd ../

ECHO Compiling bison script...
cd ./bison
win_bison.exe SintaticsParser.y -d

cd ../

ECHO Compiling all files...
gcc -march=native -Ofast -flto -Wfatal-errors -Wno-incompatible-pointer-types -Wno-all -Wextra -pedantic ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h ./symbol_table/hashtable.c -o main.exe

ECHO ----------------------------------------------------------------------------------------------------------
ECHO Executing program on VALID input:
main.exe ./input/valid_input1.txt ./output/valid_output1.log
main.exe ./input/valid_input2.txt ./output/valid_output2.log
main.exe ./input/valid_input3.txt ./output/valid_output3.log

ECHO:
ECHO ----------------------------------------------------------------------------------------------------------

ECHO Executing program on INVALID input:
main.exe ./input/invalid_input1.txt ./output/invalid_output1.log
main.exe ./input/invalid_input2.txt ./output/invalid_output2.log
main.exe ./input/invalid_input3.txt ./output/invalid_output3.log
main.exe ./input/invalid_input4.txt ./output/invalid_output4.log
main.exe ./input/invalid_input5.txt ./output/invalid_output5.log

ECHO:
ECHO ----------------------------------------------------------------------------------------------------------
ECHO:

del main.exe flex\LessicalParser.c bison\SintaticsParser.tab.c bison\SintaticsParser.tab.h