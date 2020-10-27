#ifndef __alloc_h__
#define __alloc_h__

#include "linkedList.h"
#include "util.h"

#include <stdlib.h>
#include <stddef.h>

#define MAGIC 0x144b36e8;
#define CHUNK 0x4000

struct header{
	int magic;
	size_t size;
};

const size_t HEADER_SIZE = sizeof(struct header);
void* alloc_getVoid(void* start);
void* Mem_Alloc(int size);
void* alloc_extend(size_t size);
#endif