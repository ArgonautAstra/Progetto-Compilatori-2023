#! /bin/bash
echo "Compiling flex script..."
cd ./flex
flex LessicalParser.fl

cd ../

echo "Compiling bison script..."
cd ./bison
bison SintaticsParser.y -d

cd ../

echo "Compiling all files..."
gcc -march=native -Ofast -flto -Wfatal-errors -Wall -Wextra -pedantic ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h ./symbol_table/hashtable.c -o main.out

./main.out ./input/input.txt ./output/output.txt
./main.out ./input/input2.txt ./output/output2.txt
./main.out ./input/input3.txt ./output/output3.txt
rm main.out ./flex/LessicalParser.c ./bison/SintaticsParser.tab.c ./bison/SintaticsParser.tab.h