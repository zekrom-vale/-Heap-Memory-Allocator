#ifndef INIT_H
#define INIT_H

#include <stdlib.h>

#include "alloc.h"
#include "linkedList.h"
#include "alloc.h"

int Mem_Free(void* ptr);
struct linkedList* init_list(struct linkedList* ptr);

#endif