#include "init.h"

/**
*requests a new chunk of memory
*@param size the size of the block
*/
void* init_request(size_t size){
	void* v=mmap(
		NULL,
		size,
		PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS,
		//Don't need file device (fd) with MAP_ANONYMOUS
		0,
		#if PAGE
		sysconf(_SC_PAGE_SIZE)
		#else
		0
		#endif
	);
	if(v == MAP_FAILED){
		//perror("mmap");
		return NULL;
	}
    return v;
}

void* Mem_Init(int sizeOfRegion){
  if (sizeOfRegion <= 0 || sizeOfRegion > MAX_SIZE) {
		m_error = E_BAD_ARGS;
		return NULL;
	}
	//Pass 0 to default to CHUNK
	size_t size = sizeOfRegion == 0 ?
		CHUNK : sizeOfRegion;
	struct header* start=alloc_extend(size + LIST_HEAD);
	linked_list_init(start);
	void* it = start + 1;
	linked_list_add(it, size);
	return it;
	// |h|H|h|h|h| | | | | | |
}
