# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

#defines the files to use
cfiles=init.c free.c linkedList.c alloc.c dump.c mem.c util.c listFind.c error.c
hfiles=init.h free.h linkedList.h alloc.h dump.h mem.h util.h listFind.h error.h

all:
	memory main

memory: $(cfiles) $(hfiles)
	gcc -c -fpic $(cfiles) -o mem$(objsuf) -Wall -Werror
	gcc -shared -o libmem$(shasuf) mem$(objsuf)

memdirect: $(cfiles) $(hfiles) main.c
	gcc $(cfiles) $(hfiles) main.c -o memdir$(objsuf)

setPath:
	export OLD_LD_LIBRARY_PATH=$$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH

restorePath:
	export LD_LIBRARY_PATH=$$OLD_LD_LIBRARY_PATH

main: memory setPath
	gcc -L. -o main$(objsuf) main.c -Wall -Werror -lmem

clean: restorePath
	rm mem$(objsuf)