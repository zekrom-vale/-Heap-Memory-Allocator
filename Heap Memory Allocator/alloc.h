#ifndef ALLOC_H
#define ALLOC_H

#include "linkedList.h"
#include "util.h"
#include "mem.h"
#include <stdlib.h>
#include <stddef.h>

extern const int MAGIC;
extern const int CHUNK;
extern const size_t HEADER_SIZE;

struct header{
	int magic;
	size_t size;
};

void* alloc_getVoid(struct header* start);
void* Mem_Alloc(int size);
struct header* alloc_extend(size_t size);
#endif