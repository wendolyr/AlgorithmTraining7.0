CC = g++
FLAGS = -Wall -Werror -Wextra -Wpedantic -std=c++20
FILE_PATH = task_C.cc

all: clean build

build:
	$(CC) $(FLAGS) $(FILE_PATH)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./a.out < test.txt

clean:
	rm -rf *.out
