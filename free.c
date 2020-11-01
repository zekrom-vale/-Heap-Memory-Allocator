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
	if(head->magic != MAGIC)exit(E_PADDING_OVERWRITTEN);
	struct node* node=linked_list_add(head, head->size);
	//If coalescing call it
#if COALESCE
	linked_list_coalesce(node);
#endif
	return 0;
}
