.PHONY: hello int array return object

CC=clang

all: hello int array object module variable

hello: hello.c
	$(CC) -std=c99 -Wall -o hello hello.c -lmruby -lm

int: int.c
	$(CC) -std=c99 -Wall -o int int.c -lmruby -lm

array: array.c
	$(CC) -std=c99 -Wall -o array array.c -lmruby -lm

return: return.c
	$(CC) -std=c99 -Wall -o return return.c -lmruby -lm

object: object.c
	$(CC) -std=c99 -Wall -o object object.c -lmruby -lm

module: module.c
	$(CC) -std=c99 -Wall -o module module.c -lmruby -lm

variable: variable.c
	$(CC) -std=c99 -Wall -o variable variable.c -lmruby -lm
