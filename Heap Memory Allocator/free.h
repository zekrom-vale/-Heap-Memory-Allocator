#ifndef __free_h__
#define __free_h__

#include "alloc.h"
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>

int Mem_Free(void* ptr);
struct header* getHead(void* start);

#endif