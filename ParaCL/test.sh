#!/bin/bash

# The first argument of the script is the name of tesing binary file
BIN=$1

INPUT_DIR="test/Lexer/input/"
GOLDEN_DIR="test/Lexer/golden"
OUTPUT_DIR="tmp/out/"

# Check that the testing file exists
if [[ $BIN == "" ]] ;
then
    echo "[ERROR]: The testing executable is not specified."
    echo "         The file must be specified as the first argument."
    exit 1
fi

# Check that the file is executable
if [[ ! -x $BIN ]] ;
then
    echo "[ERROR]: The file under test $BIN is not executable"
    exit 2
fi

RES=0

# Testing examples
echo "Testing started;"
mkdir -p $OUTPUT_DIR
for i in `ls "$INPUT_DIR"` ;
do
    echo -n "Test: $i: "

    $BIN < "$INPUT_DIR/$i" >& $OUTPUT_DIR/"$i.sample"
    if [ `echo $?` != 0 ]
    then
    echo "Runtime error: $BIN < $INPUT_DIR/$i"
    RES=3
        continue
    fi

    diff -q "$OUTPUT_DIR/$i.sample" "$GOLDEN_DIR/$i.ans"
    if [ `echo $?` != 0 ]
    then
        RES=4
        echo "Output mismatch: diff -q "$OUTPUT_DIR/$i.sample" "$GOLDEN_DIR/$i.ans""
    else
        echo "PASS"
    fi
done

exit $RES
