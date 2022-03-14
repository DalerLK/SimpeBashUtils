#!/bin/bash

for i in b e n s t
do
    echo "TEST $i"
    ./s21_cat -$i asci.txt >s21_cat_result
    cat -$i asci.txt >cat_result
    diff -s s21_cat_result cat_result
done
rm -rf s21_cat_result cat_result