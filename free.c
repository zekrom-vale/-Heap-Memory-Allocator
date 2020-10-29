#include "free.h"

struct header* free_getHead(void* start){
	return (struct header*)start - 1;
}

int Mem_Free(void* ptr){
	struct header* head=free_getHead(ptr);

	if(head->magic != MAGIC)exit(E_PADDING_OVERWRITTEN);
	struct node* node=linked_list_add(head, head->size);
#if COALESCE
	linked_list_coalesce(node);
#endif
	return 0;
}
