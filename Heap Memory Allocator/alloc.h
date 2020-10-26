#ifndef __alloc_h__
#define __alloc_h__

#include "linkedList.h"

#include <stdlib.h>
#include <stddef.h>

#define MAGIC 0x144b36e8;
#define CHUNK 0x4000

struct header{
	int magic;
	size_t size;
};

const size_t HEADER_SIZE = sizeof(struct header);
void* getVoid(void* start);
void* Mem_Alloc(int size);
void* extend(size_t size);
#endif