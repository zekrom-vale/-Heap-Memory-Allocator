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
		//Don't need file device (fd) with MAP_ANONYMOUS
		0,
		sysconf(_SC_PAGE_SIZE)
	);
	if(v == MAP_FAILED){
		perror("mmap");
		return NULL;
	}
    return v;
}

void* Mem_Init(int sizeOfRegion){
	//Pass 0 to default to CHUNK
	size_t size = sizeOfRegion == 0 ?
		CHUNK : sizeOfRegion;
	void* start=extend( size + LIST_HEAD);
	init(start);
	void* it = start + LIST_HEAD;
	add(it, size);
	return it;
	// |h|H|h|h|h| | | | | | |
}
