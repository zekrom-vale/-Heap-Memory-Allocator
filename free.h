#ifndef FREE_H
#define FREE_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "alloc.h"
#include "error.h"
#include "linkedList.h"
#include "mem.h"
#include "util.h"

/**
 * If true coalesce the free space
 */
#define COALESCE true

int Mem_Free(void* ptr);
struct header* free_getHead(void* start);
struct node* linked_list_coalesce(struct node* start);

#endif
