#include "free.h"


/** 
 * Gets the header from the start space
 * @param start the start of the space used by the user
 * @return the header of the space
 */
struct header* free_getHead(void* start){
	return (struct header*)start - 1;
}

/**
 * Frees the given memory
 * @param ptr the starting location of the given memory
 * @return 0
 */
int Mem_Free(void* ptr){
	struct header* head=free_getHead(ptr);

	//validates the header
	error_head(head);
	struct node* node=linked_list_add(head, head->size);
	//If coalescing call it
#if COALESCE
	free_coalesce(node);
#endif
	return 0;
}

/**
 * coalesces the linked list
 * If USE_END it will coalesce the previous node, if not it will only do the next node
 * It is not optimal when USE_END is false due to the posiblilty of non  coalesced free space
 * @param start the node to coalesce arround
 */
struct node* free_coalesce(struct node* start) {
  struct node* next = util_ptrAdd(list_find_getNodeEnd(start)+1,1);
	if(linked_list_validate(next)){
		start->size+=next->size;
		linked_list_remove(next);
#if USE_END
		start->end=next->end;
		start->end->start=start;
#endif
	}
#if USE_END
	struct node* prev = list_find_getPrevNode(start);
	if(prev!=NULL){
		prev->size+=start->size;
		linked_list_remove(start);
		prev->end=next->end;
		prev->end->start=prev;
		return prev;
	}
#endif
	return start;
}
