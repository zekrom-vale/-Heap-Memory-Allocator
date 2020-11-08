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

/** 
 * If true coalesce the free space
 */
#define COALESCE true

int Mem_Free(void* ptr);
struct header* free_getHead(void* start);
struct node* linked_list_coalesce(struct node* start);

#endif