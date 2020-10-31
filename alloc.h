#ifndef ALLOC_H
#define ALLOC_H

#include "linkedList.h"
#include "util.h"
#include "mem.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define MAGIC 0x144b36e8
#define CHUNK 0x4000UL
#define EXPAND true
#define ALIGN 0x8 //0x1 to disable

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