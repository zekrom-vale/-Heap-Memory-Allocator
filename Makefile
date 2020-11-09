# Make Makefile use bash
SHELL := /bin/bash
# Suffix for object files
objsuf=.o
# Suffix for shared object files
shasuf=.so

gcc=gcc -std=gnu++98 -std=gnu99
err=-Wall -Werror

#defines the files to use
files=init free linkedList alloc dump mem util listFind error extend
hfiles:=$(foreach file, $(files), $(file).h) config.h
cfiles:=$(foreach file, $(files), $(file).c)

all:
	memory main

memory: $(cfiles) $(hfiles)
	$(gcc) -c -fpic $(cfiles) -o mem$(objsuf) $(err)
	$(gcc) -shared -o libmem$(shasuf) mem$(objsuf)

memdirect: $(cfiles) $(hfiles) main.c
	$(gcc) $(cfiles) $(hfiles) main.c -o memdir$(objsuf)

setPath:
	export OLD_LD_LIBRARY_PATH=$$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH

restorePath:
	export LD_LIBRARY_PATH=$$OLD_LD_LIBRARY_PATH

main: memory setPath
	$(gcc) -L. -o main$(objsuf) main.c $(err) -lmem

clean: restorePath
	rm mem$(objsuf)