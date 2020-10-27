#ifndef __free_h__
#define __free_h__

#include "alloc.h"
#include "linkedList.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int Mem_Free(void* ptr);
struct header* free_getHead(void* start);

#endif