# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

#Pass other command line arguments
opt=

dbg=
dbgf=

#Pass gdb=<any value> to debug instead of running
ifdef gdb
dbg=gdb
dbgf=-d
endif

gcc=gcc $(dbgf) -std=gnu99
def=$(opt) -DWSL=false -DMAX_SIZE=1.074e9L
err=-Wall

#defines the files to use
hfiles=init.h free.h linkedList.h alloc.h dump.h mem.h util.h listFind.h error.h extend.h config.h
cfiles=init.c free.c linkedList.c alloc.c dump.c mem.c util.c listFind.c error.c extend.c
#gcc forces the creation of all objects with this format, -c cannot be used to specify -o with multiple files
ofiles=init.o free.o linkedList.o alloc.o dump.o mem.o util.o listFind.o error.o extend.o

all: memory main

memory: $(cfiles) $(hfiles)
	$(gcc) $(def) -c $(err) -fpic $(cfiles)
	$(gcc) -shared -o libmem.so $(ofiles)

memdirect: $(cfiles) $(hfiles) main.c
	$(gcc) $(def) $(err) $(cfiles) $(hfiles) main.c -o maindir$(objsuf)

setPath:
	export LD_LIBRARY_PATH=$(CURDIR):$$LD_LIBRARY_PATH

restorePath:
	unset LD_LIBRARY_PATH

main: memory setPath mem.h config.h
	$(gcc) -L. -o main$(objsuf) main.c $(err) -lmem

flags=default small break breakNeg breakZero breakBad breakNULL breakOffset
space= ================================================ 
run: main
	for f in $(flags) ; do \
		echo $(space); \
		echo ./main$(objsuf) $$f; \
		echo $(space); \
		$(dbg) ./main$(objsuf) $$f; \
		read -n 1 -s -r -p "Press any key to continue"; \
		echo ; \
	done

rundirect: memdirect
	for f in $(flags) ; do \
		echo $(space); \
		echo ./maindir$(objsuf) $$f; \
		echo  $(space); \
		$(dbg) ./maindir$(objsuf) $$f; \
		read -n 1 -s -r -p "Press any key to continue"; \
		echo ; \
	done

clean: restorePath
	rm *.so *.o *.gch
