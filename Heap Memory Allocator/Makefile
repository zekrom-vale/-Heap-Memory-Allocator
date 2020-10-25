all:
	mem

mem: init.c free.c linkedList.c alloc.c dump.c main.c mem.c \
	init.h free.h linkedList.h alloc.h dump.h mem.h 
	gcc init.c free.c linkedList.c alloc.c dump.c main.c mem.c -o mem.o

clean:
	rm mem.o