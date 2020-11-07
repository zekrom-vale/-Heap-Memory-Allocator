#ifndef ALLOC_H
#define ALLOC_H

#include "linkedList.h"
#include "listFind.h"
#include "util.h"
#include "mem.h"
#include "error.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

/** 
 * The magic value to validate headers
 */
#define MAGIC 0x144b36e8
/** 
 * The chunk of space to allocate at a time
 * mmaped space will be rounded to this value
 * Should be a factor of ALIGN
 */
#define CHUNK 0x4000UL
/** 
 * When true expand the mmaped space
 */
#define EXPAND true
/** 
 * The amount to align allocated space by
 * Rounds up allocated space to this ammount
 * Use 0x1 to disable
 */
#define ALIGN 0x8

/** 
 * The header of the allocated space
 * @member magic the validation constant of the header
 * @member size the size of the allocated space
 */
struct header{
	int magic;
	size_t size;
};

void* alloc_getVoid(struct header* start);
void* Mem_Alloc(int size);
struct header* alloc_extend(size_t size);
struct header* alloc_extendInit(size_t size);
size_t alloc_calcSpace(size_t size);
#endif