#include "init.h"

/**
*requests a new chunk of memory
*@param size the size of the block
*/
void* request(size_t size){
	void* v=mmap(
		NULL,
		size,
		PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS,
		0,
		sysconf(_SC_PAGE_SIZE)
	);
    return v==MAP_FAILED?NULL:v;
}

void* Mem_Init(int sizeOfRegion){
	void* start=request((size_t)sizeOfRegion + LIST_HEAD);
	init(start);
	void* it = start + LIST_HEAD;
	add(it, (size_t)sizeOfRegion);
	return it;
	// |h|H|h|h|h| | | | | | |
}
