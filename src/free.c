#include "alloc.c"
#include "linkedList.c"

struct header* getHead(void* start){
	return (struct header*)(start-HEADER_SIZE);
}

int Mem_Free(void* ptr){
	struct header head=getHead(ptr);
	assert(head->magic==MAGIC);
	size_t size=head->size;
	coalesce(add((void*)head, size));
	return 0;
}
