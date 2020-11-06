#include "alloc.h"

/**
 * Returns the starting location of the space
 * @param start the location of the heaer
 * @return the pointer of the free/allocd space
 */
void* alloc_getVoid(struct header* start){
	return start + 1;
}

/**
 * Alocates new space to be used
 * @param size the minimum size to allocate
 * If the size is less than the ATOMIC size it will allocate the atomic size
 * If not a factor of ALIGN (0x8) it will round up
 * If the remaning free space is less than ATOMIC it will include that space
 * @return The pointer to the starting space of the allocated space
 */
void* Mem_Alloc(int size){
	error_args(size);
	size_t s = (size_t)util_roundUp(
	  size + sizeof(struct header),
	  ALIGN
	);
	void* start=list_find(&s);
	if(start!=NULL){
		struct header* head=(struct header*)start;
		head->magic=MAGIC;
		head->size=s; //If atomic size is too small s is updated
		return alloc_getVoid(start);
	}
	else{
		#if EXPAND
		return alloc_getVoid(extend_extend((size_t)size));
		#else
			error_noSpace();
		#endif
	}
}
