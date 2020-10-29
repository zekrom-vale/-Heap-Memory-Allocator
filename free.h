#ifndef FREE_H
#define FREE_H

#include "alloc.h"
#include "linkedList.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

#define COALESCE false

int Mem_Free(void* ptr);
struct header* free_getHead(void* start);

#endif