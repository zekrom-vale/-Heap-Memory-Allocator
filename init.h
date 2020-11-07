#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mem.h"
#include "linkedList.h"
#include "alloc.h"

/**
 * Fix MAP_ANONYMOUS not defined
 * Likely an issue with Visual Studio and WSL
 */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS   0x20
#define MAP_ANON        MAP_ANONYMOUS
#endif
/** 
 * If true pass the page size to mmap, 0 otherwise
 */
#define PAGE false

void* init_request(size_t size);
int Mem_Free(void* ptr);
struct linkedList* init_list(struct linkedList* ptr);

#endif