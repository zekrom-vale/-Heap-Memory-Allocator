#ifndef ALLOC_H
#define ALLOC_H

#include "linkedList.h"
#include "util.h"
#include "mem.h"
#include <stdlib.h>
#include <stddef.h>

const int MAGIC = 0x144b36e8;
const int CHUNK = 0x4000;

struct header{
	int magic;
	size_t size;
};

const size_t HEADER_SIZE = sizeof(struct header);
void* alloc_getVoid(struct header* start);
void* Mem_Alloc(int size);
struct header* alloc_extend(size_t size);
#endif