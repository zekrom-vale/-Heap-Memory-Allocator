#ifndef LIST_FIND_H
#define LIST_FIND_H

#include <stdlib.h>

#include "error.h"
#include "linkedList.h"
#include "mem.h"

void* list_find(size_t* s);
void* list_find_findFirstFit(size_t* s);
void* list_find_findWorstFit(size_t* s);
void* list_find_findBestFit(size_t* s);

struct node* list_find_offset(struct node* start, size_t size);
struct nodeEnd* list_find_getNodeEnd(struct node* start);
struct node* list_find_getPrevNode(struct node* start);
struct node* list_find_getNextNode(struct node* cur);
#endif
