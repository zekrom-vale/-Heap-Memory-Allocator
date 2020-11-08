#ifndef EXTEND_H
#define EXTEND_H

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "error.h"
#include "linkedList.h"
#include "mem.h"
#include "util.h"

/**
 * Fix MAP_ANONYMOUS not defined
 * Likely an issue with Visual Studio and
 * WSL
 */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS
#endif

struct frame{
	size_t size;
	struct frame* next;
};

void* extend_request(size_t size);
struct header* extend_extend(size_t size);
struct header* extend_extendInit(size_t size);

#endif
