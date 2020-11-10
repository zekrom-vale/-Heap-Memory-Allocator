# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

opt=

gcc=gcc -std=gnu++98 -std=gnu99
def=-DWSL=false -DMAX_SIZE=1.074e9L $(opt)
err=-Wall -Werror

#defines the files to use
hfiles=init.h free.h linkedList.h alloc.h dump.h mem.h util.h listFind.h error.h extend.h config.h
cfiles=init.c free.c linkedList.c alloc.c dump.c mem.c util.c listFind.c error.c extend.c

all:
	memory main

memory: $(cfiles) $(hfiles)
	$(gcc) $(def) -c -fpic $(cfiles) -o mem$(objsuf) $(err)
	$(gcc) -shared -o libmem$(shasuf) mem$(objsuf)

memdirect: $(cfiles) $(hfiles) main.c
	$(gcc) $(def) $(cfiles) $(hfiles) main.c -o memdir$(objsuf)

setPath:
	export OLD_LD_LIBRARY_PATH=$$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH

restorePath:
	export LD_LIBRARY_PATH=$$OLD_LD_LIBRARY_PATH

main: memory setPath
	$(gcc) -L. -o main$(objsuf) main.c $(err) -lmem

clean: restorePath
	rm mem$(objsuf)