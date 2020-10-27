#ifndef __linkedList_h__
#define __linkedList_h__

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "init.h"
#include "mem.h"
#include "util.h"


struct node{
	struct node* next;
	struct node* prev;
	size_t size;
	struct nodeEnd* end;
};

struct nodeEnd{
	struct node* start;
};


struct linkedList{
	struct node* first;
	struct node* last;
	int size;
	int MODE : FIRSTFIT;
};

extern struct linkedList* LIST;

const size_t LIST_HEAD = sizeof(struct linkedList);

/**
*The size of the end node
*/
const size_t END = sizeof(struct nodeEnd);

/**
*The absolute minumum of the free space
*It is posible to allocate if the size is the same as struct node, but that requres more logic
*/
const size_t ATOMIC = sizeof(struct node) + END;

struct node* linked_list_offset(struct node* start,size_t size);
struct nodeEnd* linked_list_getNodeEnd(struct node* start);
bool linked_list_validate(struct node* start,struct nodeEnd* end);
struct node* linked_list_getPrevNode(struct node* start);
struct linkedList* linked_list_init();
struct node* linked_list_add(void* start,size_t size);
void linked_list_remove(struct node* n);
void linked_list_shift(struct node* start,size_t size);
void linked_list_coalesce(struct node* start);
void* linked_list_find(size_t* s);
void* linked_list_findFirstFit(size_t* s);
void* linked_list_findWorstFit(size_t* s);
void* linked_list_linked_list_findBestFit(size_t* s);
void linked_list_sort();
void linked_list_print();
#endif