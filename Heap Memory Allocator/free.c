#include "free.h"

struct header* getHead(void* start){
	return (struct header*)ptrSub(start, HEADER_SIZE);
}

int Mem_Free(void* ptr){
	struct header* head=getHead(ptr);
	assert(head->magic==MAGIC);
	size_t size=head->size;
	coalesce(add(head, size));
	return 0;
}
