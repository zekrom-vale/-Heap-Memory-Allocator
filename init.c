#include "init.h"

/**
 * requests a new chunk of memory
 * @param size the size of the block
 * @return the pointer of the start of the mmap
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

/**
 * Initalises the first chunk of mmaped memory
 * If this space runs out it will be automaticaly expaded relative to the size of the requested memory, but enough for multiple allocations
 * @param sizeOfRegion The size of the memory, this will be rounded to the nerest CHUNK
 * @return the pointer for the mmaped location
 * Cast this to struct linkedList* to use it
 */
void* Mem_Init(int sizeOfRegion){
  if (sizeOfRegion < 0 || sizeOfRegion > MAX_SIZE) {
		m_error = E_BAD_ARGS;
		return NULL;
	}
	//Pass 0 to default to CHUNK
	size_t size = sizeOfRegion == 0 ?
		CHUNK : sizeOfRegion;
	return alloc_extendInit(size);
	// |h|H|h|h|h| | | | | | |
}
