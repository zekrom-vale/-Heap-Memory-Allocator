# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

all:
	mem

mem: init.c free.c linkedList.c alloc.c dump.c main.c mem.c \
	init.h free.h linkedList.h alloc.h dump.h mem.h 
	gcc -c -fpic init.c free.c linkedList.c alloc.c \
		dump.c main.c mem.c -o mem$(objsuf) -Wall -Werror
	gcc -shared -o libmem$(shasuf) mem$(objsuf)

main: mem
	gcc -L. -o main$(objsuf) main.c -Wall -Werror -lmem

clean:
	rm mem$(objsuf)