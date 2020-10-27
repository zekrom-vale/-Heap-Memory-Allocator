#include "free.h"

struct header* free_getHead(void* start){
	return (struct header*)start - 1;
}

int Mem_Free(void* ptr){
	struct header* head=free_getHead(ptr);
	assert(head->magic==MAGIC && "Magic Missmatch");
	linked_list_coalesce(linked_list_add(head, head->size));
	return 0;
}
