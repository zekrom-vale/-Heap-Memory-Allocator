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

struct node* offset(struct node* start,size_t size);
struct nodeEnd* getNodeEnd(struct node* start);
bool validate(struct node* start,struct nodeEnd* end);
struct node* getPrevNode(struct node* start);
struct linkedList* init();
struct node* add(void* start,size_t size);
void remove(struct node* n);
void shift(struct node* start,size_t size);
void coalesce(struct node* start);
void* find(size_t* s);
void* findFirstFit(size_t* s);
void* findWorstFit(size_t* s);
void* findBestFit(size_t* s);
void sort();
void print();
#endif