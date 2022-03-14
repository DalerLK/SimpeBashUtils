all: clear s21_grep

s21_grep:
		gcc s21_grep.c -o s21_grep
clear:
		rm -rf s21_grep *.cfg
test:
		chmod +x script.sh
		./script.sh
linter:
		cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
		python3 ../../materials/linters/cpplint.py --extension=c *.c
leaks:
		CK_FORK=no leaks --atExit -- ./s21_grep -f test3.txt asci.txt

phony: s21_grep test