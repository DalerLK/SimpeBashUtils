#!/bin/bash

for i in i v c l n h o e
do
    echo "TEST $i"
    ./s21_grep -$i them asci.txt >s21_grep_result
    grep -$i them asci.txt >grep_result
    diff -s s21_grep_result grep_result
done

echo "TEST f"
    ./s21_grep -f test2.txt asci.txt >s21_grep_result
    grep -f test2.txt asci.txt >grep_result
    diff -s s21_grep_result grep_result

echo "TEST s"
    ./s21_grep -s asci.t >s21_grep_result
    grep -s them asci.t >grep_result
    diff -s s21_grep_result grep_result


rm -rf s21_grep_result grep_result
