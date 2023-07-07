#! /bin/bash
echo "Compiling flex script"
cd ./flex
flex LessicalParser.fl

echo "Compiling lex.yy file"
gcc LessicalParser.c -o ../main.out
rm LessicalParser.c
cd ../

echo "Scanning of input1"
./main.out ./input/test.txt ./output/test.log