#ifndef ALLOC_H
#define ALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "error.h"
#include "extend.h"
#include "mem.h"
#include "config.h"

/**
 * The header of the allocated space
 * @member magic the validation constant of the header
 * @member size the size of the allocated space
 */
struct header {
	int magic;
	size_t size;
};

void* alloc_getVoid(struct header* start);
void* Mem_Alloc(int size);
size_t extend_calcSpace(size_t size);
void alloc_printHeader(struct header* head);
bool alloc_validate(struct header* head);
void alloc_printHeaderMore(struct header* head);
#endif
