CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11
SOURCE = s21_string/*.c s21_sscanf/*.c s21_sprintf/*.c
UNAME := $(shell uname -s)


ifeq ($(UNAME), Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(UNAME), Darwin)
	OPEN_CMD = open
endif

all: clean s21_string.a 

test: all s21_string.a
ifeq ($(UNAME), Linux)
	gcc test.c s21_string.a -o test -lcheck -lpthread -lrt -lm -lsubunit
	./test
endif

ifeq ($(UNAME), Darwin)
	gcc -lcheck test.c s21_string.a -o test && ./test
endif

gcov_report: coverage run_coverage lcov genhtml open

coverage:
ifeq ($(UNAME), Darwin)
	gcc --coverage test.c $(SOURCE) -o test -lcheck
endif

ifeq ($(UNAME), Linux)
	gcc --coverage test.c $(SOURCE) -o test -lcheck -lpthread -lrt -lm -lsubunit
endif

run_coverage:
	./test

lcov:
	lcov -t "Core" -o s21_test.info -c -d .

genhtml:
	genhtml -o report s21_test.info

open:
	$(OPEN_CMD) ./report/index.html

s21_string.a: s21_string.o
	ar rc s21_string.a s21_*.o
	rm *.o

s21_string.o: *.c
	gcc -c $(FLAGS) $(SOURCE)

clean:
	rm -rf *.o *.a *.info *gcda *.gcno *.out test report/