# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

opt=

gcc=gcc -std=gnu99
def=-DWSL=false -DMAX_SIZE=1.074e9L $(opt)
err=-Wall

#defines the files to use
hfiles=init.h free.h linkedList.h alloc.h dump.h mem.h util.h listFind.h error.h extend.h config.h
cfiles=init.c free.c linkedList.c alloc.c dump.c mem.c util.c listFind.c error.c extend.c
ofiles=init$(objsuf) free$(objsuf) linkedList$(objsuf) alloc$(objsuf) dump$(objsuf) mem$(objsuf) util$(objsuf) listFind$(objsuf) error$(objsuf) extend$(objsuf)

all: memory main

memory: $(cfiles) $(hfiles)
	$(gcc) $(def) -c $(err) -fpic $(cfiles)
	$(gcc) -shared -o libmem.so $(ofiles)

memdirect: $(cfiles) $(hfiles) main.c
	$(gcc) $(def) $(err) $(cfiles) $(hfiles) main.c -o memdir$(objsuf)

setPath:
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH

restorePath:
	unset LD_LIBRARY_PATH

main: memory setPath mem.h config.h
	$(gcc) -L. -o main$(objsuf) main.c $(err) -lmem

run: main
	flags=(default small break breakNeg breakZero breakBad breakNULL)
	for f in $${flags[@]}; do \
		echo ./main$(objsuf) $${flags[$$f]} \
		./main$(objsuf) $${flags[$$f]} \
		echo \
	done

rundirect: memdirect
	flags=(default small break breakNeg breakZero breakBad breakNULL)
	for f in $${flags[@]}; do \
		echo ./maindir$(objsuf) $${flags[$$f]} \
		./maindir$(objsuf) $${flags[$$f]} \
		echo \
	done

clean: restorePath
	rm mem$(objsuf)
	rm *.o