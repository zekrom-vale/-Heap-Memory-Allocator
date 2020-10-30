#ifndef ALLOC_H
#define ALLOC_H

#include "linkedList.h"
#include "util.h"
#include "mem.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

extern const int MAGIC;
extern const int CHUNK;
extern const size_t HEADER_SIZE;
#define EXPAND true

struct header{
	int magic;
	size_t size;
};

void* alloc_getVoid(struct header* start);
void* Mem_Alloc(int size);
struct header* alloc_extend(size_t size);
struct header* alloc_extendInit(size_t size);
size_t alloc_calcSpace(size_t size);
#endif