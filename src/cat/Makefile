all: clear s21_cat

s21_cat:
	gcc s21_cat.c -o s21_cat
clear:
	rm -rf s21_cat *.cfg
test:
	chmod +x script.sh
	./script.sh
linter:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c
leaks:
	CK_FORK=no leaks --atExit -- ./s21_cat asci.txt

phony: s21_cat test