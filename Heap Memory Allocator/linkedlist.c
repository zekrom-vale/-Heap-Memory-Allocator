#include "linkedList.h"

/**
*gets the next location of the node
*@param start the original node
*@param size the offset
*/
struct node* offset(struct node* start, size_t size){
	assert(size > ATOMIC);
	struct node* next = (struct node*)ptrAdd(start, size + 1);
	return next;
}

/**
*returns the location of the end of the node
*@param start the node to get the end of
*/
struct nodeEnd* getNodeEnd(struct node* start){
	return (struct nodeEnd*)ptrAdd(start, start->size-END);
	//|x|x|x|x|x|x|x|x|x| | | | | | | | | | | | |e|e|e|e| |
	// 0                 1                   2
	// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
}

/**
*validates the given node
*@code{validate(node, node->end);}
*@param start the node to verify
*@param end the corisponding end node to validate
*/
bool validate(struct node* start, struct nodeEnd* end){
	if(start==NULL||end==NULL)return false;
	return start->end==end;
}

struct node* getPrevNode(struct node* start){
	//|e|e|e|e|x|x|x|x|x|
	struct nodeEnd* end=(struct nodeEnd*)ptrSub(start, END);
	if(!validate(end->start, end))return NULL;
	return end->start;
}

/**
*Creates the linkedList
*/
struct linkedList* init(void* ptr){
	LIST = (struct linkedList*)ptr;
	LIST->first=NULL;
	LIST->last=NULL;
	LIST->size=0;
	return LIST;
}

void* readd(struct node* n){
	if(LIST->first == NULL){
		n->next == NULL;
		n->prev == NULL;
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
	LIST->size++;
}

/**
*adds the given location with the given size
*this DOES NOT coalesce
*@param start the space to add
*@param size the size of the node
*/
struct node* add(void* start, size_t size){
	struct node* n=(struct node*)start;
	n->end=getNodeEnd(start);
	n->end->start=n;
	readd(n);
	return n;
}

/**
*removes the given node
*@param n the node to remove
*/
void remove(struct node* n){
	assert(LIST->size!=0);
	assert(n!=NULL);
	//Clear the end noe
	struct nodeEnd* end=n->end;
	assert(validate(n, end));
	end->start=NULL;
	//Attach the next and perv to eachother if they exist
	//If not update the LIST
	struct node* prev = n->prev;
	struct node* next=n->next;
	if(next!=NULL)next->prev=prev;
	else LIST->last=prev;
	if(prev!=NULL)prev->next=next;
	else LIST->first=next;
	LIST->size--;
	//dealocate node
}

/**
*shifts the given node the given size
*@param start the node to shift
*@param size the size to offest
*/
void shift(struct node* start, size_t size){
	struct node* newstart = offset(start,size);
	struct node* next = start->next;
	struct node* prev=start->prev;
	//Update end node

	struct nodeEnd* end=start->end;
	end->start=newstart;

	//copy to new node
	newstart->next=next;
	newstart->prev=prev;
	newstart->size=start->size-size;
	newstart->end=end;

	//re-point other nodes

	struct node* prev = start->prev;
	struct node* next=start->next;
	if(next!=NULL)next->prev=newstart;
	else LIST->last=newstart;
	if(prev!=NULL)prev->next=newstart;
	else LIST->first=newstart;
}

/**
*coalesces the linked list
*@param start the node to coalesce arround
*/
void coalesce(struct node* start){
	struct node* next=offset(start, start->size);
	struct node* prev=getPrevNode(start);
	if(next!=NULL){
		start->size+=next->size;
		remove(next);
		start->end=next->end;
		start->end->start=start;
	}
	if(prev!=NULL){
		prev->size+=start->size;
		remove(start);
		prev->end=next->end;
		prev->end->start=prev;
	}
}

/**
*Finds the next space avalbe
*@param s the size to find, updated if remaning space is not attomic
*@return a pointer to the allocated space, NULL if not found (Does not expand memory)
*/
void* find(size_t* s){
	switch(MODE){
		case FIRSTFIT:
			return findFirstFit(s);
		case BESTFIT:
			return findBestFit(s);
		case WORSTFIT:
			return findWorstFit(s);
	}
}

void* process(size_t* s,struct node* start){
	if(start->size < s){
		//Failure space is too small
		return NULL;
	}
	// If the remaning space is not attomic allocate more and update s
	size_t min = *s + ATOMIC;
	if(start->size < min){
		*s = min;
		remove(start);
	}
	//Otherwise just sift it
	else shift(start,*s);
	//Return the location of the space
	return start;
}

void* findFirstFit(size_t* s){
	struct node* cur=LIST->first;
	size_t size=*s;
	while(cur!=NULL){
		//If the size is larger than requested
		if(cur->size>=size){
			//If a perfect match
			if(cur->size==size){
				remove(cur);
				return cur;
			}
			return procss(s, cur);
		}
	}
	//Failure
	return NULL;
}

void* findWorstFit(size_t* s){
	struct node* cur = LIST->first;
	struct node* large = cur;
	size_t size = *s;
	while(cur != NULL){
		//If the size is larger than requested
		if(cur->size >= size){
			//If a perfect match
			if(cur->size == size){
				remove(cur);
				return cur;
			}
			//If cur is larger replace large
			if(cur->size > large->size)large=cur;
		}
	}
	return procss(s, large);
}


void* findBestFit(size_t* s){
	struct node* cur = LIST->first;
	struct node* small = cur;
	size_t size = *s;
	while(cur != NULL){
		//If the size is larger than requested
		if(cur->size >= size){
			//If a perfect match
			if(cur->size == size){
				remove(cur);
				return cur;
			}
			//If cur is larger replace large
			if(
				cur->size > size
				&& 
				cur->size < small->size
			)small = cur;
		}
	}
	return procss(s, small);
}

void swap(struct node* A, struct node* B){
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

void addat(struct node* before, struct node* n){
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

void sortInsert(struct node* cur, struct node* new){
	if(cur == NULL)readd(new);
	else if(cur > new)addat(cur, new);
	else{
		while(cur->next != NULL && cur->next < new)
			cur = cur->next;
		addat(cur, new);
	}
}

void sort(){
	struct node* sort = NULL;
	struct node* cur = LIST->first;
	while(cur!=NULL){
		struct node* next = cur->next;
		remove(cur);
		sortInsert(sort, cur);
		cur = next;
	}
}

#include <stdio.h>
void print(){
	struct node* cur = LIST->first;
	while(cur!=NULL){
		printf("%p\n",cur);
		cur = cur->next;
	}
}