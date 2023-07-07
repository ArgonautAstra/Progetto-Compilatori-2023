#! /bin/bash
echo "Compiling flex script"
cd ./flex
flex LessicalParser.fl

echo "Compiling lex.yy file"
gcc LessicalParser.c -o ../main.out
cd ../

echo "Scanning of input1"
./main.out ./input/test.txt ./output/test.log