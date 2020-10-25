#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

struct node* offset(struct node* start, size_t size){
	struct node* next=(struct node*)(((void*)start)+size+1);
	if(!validate(next, next->end))return NULL;
	return next;
}

struct node{
	struct node* next;
	struct node* prev;
	size_t size;
	struct nodeEnd* end;
}

struct nodeEnd{
	struct node* start;
}

static const size_t END = sizeof(struct nodeEnd);
static const size_t ATOMIC = sizeof(struct node)+END;

struct nodeEnd* getNodeEnd(struct node* start){
	return (struct nodeEnd*)((void*)start+start->size-END);
	//|x|x|x|x|x|x|x|x|x| | | | | | | | | | | | |e|e|e|e| |
	// 0                 1                   2
	// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
}

bool validate(struct node* start, struct nodeEnd* end){
	if(start==NULL||end==NULL)return false;
	return start->end==end;
}

struct node* getPrevNode(struct node* start){
	//|e|e|e|e|x|x|x|x|x|
	struct nodeEnd* end=(struct nodeEnd*)((void*)start-END);
	if(!validate(end->start, end))return NULL;
	return end->start;
}

struct linkedList{
	struct node* first;
	struct node* last;
	int size;
}

static linkedList LIST;

struct linkedList init(){
	LIST={NULL, NULL, 0};
}

void add(void* start, size_t size){
	struct node n=(struct node*)start;
	n->end=getNodeEnd(start);
	n->end->start=n;
	if(LIST->first==NULL){
		n->next==NULL;
		n->prev==NULL;
		LIST->first=n;
		LIST->last=n;
	}
	else{
		struct node* last=LIST->last;
		LIST->last=n;
		n->next=NULL;
		n->prev=last;
		last->next=n;
	}
	LIST->size++;
}


void remove(struct node* n){
	assert(LIST->size!=0);
	assert(n!=NULL);
	struct nodeEnd* end=n->end;
	assert(validate(n, end));
	end->start=NULL;
	/*
	if(LIST->size==1){
		LIST->next=NULL;
		LIST->prev=NULL;
	}
	else{
		if(LIST->first==n){
			LIST->first=n->next;
			LIST->first->prev=NULL;
		}
		else if(List->last==n){
			LIST->last=n->prev;
			LIST->last->next=NULL;
		}
		else{
			struct node* prev=n->prev,
				next=n->next;
			prev->next=next;
			next->prev=prev;
		}
	}*/

	struct node* prev=n->prev,
		next=n->next;
	if(next!=NULL)next->prev=prev;
	else LIST->last=prev;
	if(prev!=NULL)prev->next=next;
	else LIST->first=next;
	LIST->size--;
	//dealocate node
}

void shift(struct node* start, size_t size){
	struct node* newstart=offset(start, size),
		next=start->next,
		prev=start->prev;
	//Update end node

	struct nodeEnd* end=start->end;
	end->start=newstart;

	//copy to new node
	newstart->next=next;
	newstart->prev=prev;
	newstart->size=start->size-size;
	newstart->end=end;

	//re-point other nodes

	struct node* prev=start->prev,
		next=start->next;
	if(next!=NULL)next->prev=newstart;
	else LIST->last=newstart;
	if(prev!=NULL)prev->next=newstart;
	else LIST->first=newstart;
}

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
*/
void* find(size_t& s){
	struct node* cur=LIST->first;
	size_t size=*s;
	while(cur!=NULL){
		if(cur->size>=size){
			if(cur->size==size){
				remove(cur);
				return (void*)cur;
			}
			size_t min=size+ATOMIC;
			if(cur->size<min)*s=min;
			else shift(cur, size);
			return (void*)cur;
		}
	}
	return NULL;
}
