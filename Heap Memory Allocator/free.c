#include "free.h"

struct header* getHead(void* start){
	return (struct header*)start - 1;
}

int Mem_Free(void* ptr){
	struct header* head=getHead(ptr);
	assert(head->magic==MAGIC && "Magic Missmatch");
	coalesce(add(head, head->size));
	return 0;
}
