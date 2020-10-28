#include "alloc.h"

/**
*Returns the starting location of the space
*@param start the location of the heaer
*/
void* alloc_getVoid(struct header* start){
	return start + 1;
}

void* Mem_Alloc(int size){
	if(size <= 0)exit(E_BAD_ARGS);
	size_t s=size+HEADER_SIZE;
	void* start=linked_list_find(s);
	if(start!=NULL){
		struct header* head=(struct header*)start;
		head->magic=MAGIC;
		head->size=s; //If atomic size is too small s is updated
		return alloc_getVoid(start);
	}
	else{
		return alloc_getVoid(alloc_extend(size));
	}
}

int alloc_roundUp(int num, int mult){
	return num + mult - num % mult;
}

struct header* alloc_extend(size_t size){
	//Calculate allocation size
	size_t s;
	if(size < CHUNK/0x40)s = CHUNK;
	else if(size < CHUNK/0x4)s = alloc_roundUp(0x10 * size, CHUNK);
	else s = alloc_roundUp(0x4 * size, CHUNK);
	//Request
	void* allocated = init_request(s);

	if(allocated == NULL)exit(E_NO_SPACE);

	//If size is smaller than ATTOMIC use that instead
	if(size < ATOMIC)size = ATOMIC;
	//If the allocated space is the same as the ATOMIC size
	//This should never happen with the given settings
	if(s!=ATOMIC){
		//Get the location for the free space
		linked_list_add(
			linked_list_offset((struct node*)allocated, size),
			size - s
		);
	}
	//Init header
	struct header* head = (struct header*)allocated;

	head->magic = MAGIC;
	head->size = size;
	return head;
}