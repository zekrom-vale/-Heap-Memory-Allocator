#include "init.h"

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
	return extend_extendInit(size);
	// |h|H|h|h|h| | | | | | |
}

/**
 * Creates the linkedList
 * @param ptr the start of the mmaped space
 */
struct linkedList* init_list(struct linkedList* ptr) {
  LIST = ptr;
  LIST->size = 0;
  LIST->first = NULL;
  LIST->last = NULL;
  return LIST;
}
