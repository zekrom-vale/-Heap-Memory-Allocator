#ifndef FREE_H
#define FREE_H

#include "alloc.h"
#include "linkedList.h"
#include "util.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"
#include "error.h"
#include "config.h"

int Mem_Free(void* ptr);
struct header* free_getHead(void* start);
void free_coalesce(struct node* start);

#endif