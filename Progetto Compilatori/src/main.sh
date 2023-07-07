#! /bin/bash
echo "Compiling flex script"
cd ./flex
flex LessicalParser.fl

echo "Compiling lex.yy file"
gcc LessicalParser.c -o ../main.out
rm LessicalParser.c
cd ../

echo "Scanning of input1"
./main.out ./input/input1.txt ./output/input1.log
rm main.out