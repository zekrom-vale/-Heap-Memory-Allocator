#ifndef __init_h__
#define __init_h__

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mem.h"
#include "linkedList.h"
#include "alloc.h"

//Fix MAP_ANONYMOUS not defined
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS   0x20
#define MAP_ANON        MAP_ANONYMOUS
#endif

int MODE = FIRSTFIT;

void* request(size_t size);
int Mem_Free(void* ptr);

#endif