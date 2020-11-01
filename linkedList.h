#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
//Only to provide print node nad linked list functions for other files
#include <stdio.h>
#include "init.h"
#include "mem.h"
#include "util.h"

/**
 * Should we validdate the nodes?
 * Not using this will cause crashes!!
 */
#define VALIDATE true
/** 
 * Should we create end nodes to allow for previous coalescing 
 */
#define USE_END true
/** 
 * The max size to allow for
 * There is no point to allow for memory that is phicicaly imposible
 */
#define MAX_SIZE 0.01 * 1.074e9L

/** 
 * The free space node
 * @member next the next node in the list
 * @member prev the previous node in the list
 * @member size the size of the free space
 * @member end the end of the free space, if USE_END
 */
struct node{
	struct node* next;
	struct node* prev;
	size_t size;
#if USE_END
	struct nodeEnd* end;
#endif
};

#if USE_END
/** 
 * The end of the free space to point used to linararly get the previous node
 */
struct nodeEnd{
	struct node* start;
};
#endif

/** 
 * The base of the linked list and other information
 * @member first the first node of the linked list
 * @member last the last node of the linked list
 * @member the size of the linked list
 * @member MODE the mode of the allocation
 */
struct linkedList{
	struct node* first;
	struct node* last;
	int size;
	int MODE : FIRSTFIT;
};

/** 
 * The sudo constant pointer to the linked list
 */
extern struct linkedList* LIST;
extern const size_t LIST_HEAD;
extern const size_t END;
/** 
 * The abolute minimum size of the free space or allocated space
 */
extern const size_t ATOMIC;

struct node* linked_list_offset(struct node* start,size_t size);
struct nodeEnd* linked_list_getNodeEnd(struct node* start);
bool linked_list_validate(struct node* start);
bool linked_list_validateEnd(struct nodeEnd* end);
struct node* linked_list_getPrevNode(struct node* start);
struct linkedList* linked_list_init(struct linkedList* ptr);
struct node* linked_list_add(void* start, size_t size);
void linked_list_remove(struct node* n);
void linked_list_shift(struct node* start,size_t size);
void linked_list_coalesce(struct node* start);
void* linked_list_find(size_t* s);
void* linked_list_findFirstFit(size_t* s);
void* linked_list_findWorstFit(size_t* s);
void* linked_list_findBestFit(size_t* s);
void linked_list_sort();
void linked_list_print();
void linked_list_printLinkedList();
void linked_list_printNode(struct node* cur);
#endif