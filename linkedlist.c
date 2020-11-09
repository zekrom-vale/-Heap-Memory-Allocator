/** 
 * Defines the linkedList and nodes that are used for the free space
 * Also provides utility methods to validate
 */

#include "linkedList.h"

struct linkedList* LIST;

/**
 * Validates the given node
 * @code{validate(node, node->end);}
 * @param start the node to verify
 * @param end the corisponding end node to validate
 * @return true if valid, false otherwise
 */
bool linked_list_validate(struct node* start){
#if VALIDATE
	if(start==NULL||start<LIST)return false;
#if USE_END
	struct nodeEnd* end=start->end;
	if(end<LIST)return false;
	return !(start==NULL || end==NULL || end->start != start);
#else
	if(
        cur==NULL
        ||
        cur->next!=NULL && cur->next->prev!=cur
        ||
        cur->prev != NULL && cur->prev->next != cur
    )return false;
#endif
	return true;
#endif
}

/**
 * Validates the given end node
 * This should be used with the end node rather than geting the start, as end may be invalid
 * @param start the node to verify
 * @param end the corisponding end node to validate
 * @return true if valid, false otherwise
 */
bool linked_list_validateEnd(struct nodeEnd* end) {
#if VALIDATE
  if (end == NULL || end < LIST) return false;
#if USE_END
  struct node* start = end->start;
  if(start<LIST)return false;
  return !(start == NULL || end == NULL || start->end != end);
#endif
  return true;
#endif
}

/**
 * Adds the given node back to the linked list
 * @param n the node to add back
 */
void linked_list_readd(struct node* n){
	LIST->size++;
	if(LIST->first == NULL){
		n->next = NULL;
		n->prev = NULL;
		LIST->first = n;
		LIST->last = n;
	}
	else{
		struct node* last = LIST->last;
		LIST->last = n;
		n->next = NULL;
		n->prev = last;
		last->next = n;
	}
}

/**
 * adds the given location with the given size
 * this DOES NOT coalesce
 * @param start the space to add
 * @param size the size of the node
 * @return the node created
 */
struct node* linked_list_add(void* start, size_t size){
  if (size > MAX_SIZE) exit(E_NO_SPACE);
  struct node* n = (struct node*)start;
	n->size = size;
#if USE_END
	struct nodeEnd* end=list_find_getNodeEnd(start);
	end->start=n;
	n->end=end;
#endif
	linked_list_readd(n);
	return n;
}

/**
 * removes the given node
 * @param n the node to remove
 */
void linked_list_remove(struct node* n){
	assert(LIST->size!=0);
	assert(n!=NULL);
	//Clear the end node
#if USE_END
	struct nodeEnd* end=n->end;
	linked_list_validate(n);
	end->start=NULL;
#endif
	LIST->size--;
	//Attach the next and perv to eachother if they exist
	//If not update the LIST
	struct node* prev = n->prev;
	struct node* next=n->next;
	if(next!=NULL)next->prev=prev;
	else LIST->last=prev;
	if(prev!=NULL)prev->next=next;
	else LIST->first=next;
	//dealocate node
}

/**
 * shifts the given node the given size
 * @param start the node to shift
 * @param size the size to offest
 */
void linked_list_shift(struct node* start, size_t size){
	struct node* newstart = list_find_offset(start,size);
	struct node* next = start->next;
	struct node* prev = start->prev;
	//Update end node
#if USE_END
	struct nodeEnd* end=start->end;
	end->start=newstart;
	newstart->end=end;
#endif
	//copy to new node
	newstart->next=next;
	newstart->prev=prev;
	newstart->size=start->size-size;

	//re-point other nodes

	if(next!=NULL)next->prev=newstart;
	else LIST->last=newstart;
	if(prev!=NULL)prev->next=newstart;
	else LIST->first=newstart;
}

/**
 * Swapps the nodes locaions in the linked list
 * @param A 
 * @param B 
 */
void linked_list_swap(struct node* A, struct node* B){
	if(A == B)return;
	struct node* Aprev = A->prev;
	struct node* Anext = A->next;
	if(Anext != NULL)Anext->prev = B;
	else LIST->last = B;
	if(Aprev != NULL)Aprev->next = B;
	else LIST->first = B;

	struct node* Bprev = B->prev;
	struct node* Bnext = B->next;
	if(Bnext != NULL)Bnext->prev = A;
	else LIST->last = A;
	if(Bprev != NULL)Bprev->next = A;
	else LIST->first = A;
}

void linked_list_addAt(struct node* before, struct node* n){
	assert(before != NULL);
	struct node* after = before->next;
	before->next = n;
	n->prev = before;
	if(after!=NULL){
		after->prev = n;
		n->next = after;
	}
	else{
		n->next = NULL;
		LIST->last = n;
	}
}

/**
 * Inserts the node in the right location according to address
 * @param cur the first node that is not sorted
 * @param new the new node to add
 */
void linked_list_sortInsert(struct node* cur, struct node* new){
	if(cur == NULL)linked_list_readd(new);
	else if(cur > new)linked_list_addAt(cur, new);
	else{
		while(cur->next != NULL && cur->next < new)
			cur = cur->next;
		linked_list_addAt(cur, new);
	}
}

/** 
 * Sorts the linked list via insertion sorting
 */
void linked_list_sort(){
	struct node* sort = NULL;
	struct node* cur = LIST->first;
	while(cur!=NULL){
		struct node* next = cur->next;
		linked_list_remove(cur);
		linked_list_sortInsert(sort, cur);
		cur = next;
	}
}

/** 
 * Prints the linked list of nodes
 */
//TODO swap out with that in dump.h
void linked_list_print(){
	struct node* cur = LIST->first;
	while(cur!=NULL){
		printf("%p\n",cur);
		cur = cur->next;
	}
}

/** 
 * Prints the linked list to sdtout
 */
void linked_list_printLinkedList(){
	printf(
		"struct linkedList*=%p[first=%p, last=%p, size=%zu, MODE=%d]\n",
		LIST,
		LIST->first,
		LIST->last,
		LIST->size,
		LIST->MODE
	);
}

/**
 * Prints the node to stdout
 * @param cur the node to print
 */
void linked_list_printNode(struct node* cur){
	printf(
			"struct node*=%p[next=%p, prev=%p, size=%zu, end=%p, lin_next=%p]\n",
			cur,
			cur->next,
			cur->prev,
			cur->size,
#if USE_END
			list_find_getNextNode(cur),
			cur->end
#else
			NULL,
			NULL
#endif
		);
}