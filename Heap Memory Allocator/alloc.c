#include "alloc.h"

/**
*Returns the starting location of the space
*@param start the location of the heaer
*/
void* getVoid(struct header* start){
	return start + 1;
}

void* Mem_Alloc(int size){
	size_t s=size+HEADER_SIZE;
	void* start=find(s);
	if(start!=NULL){
		struct header* head=(struct header*)start;
		head->magic=MAGIC;
		head->size=s; //If atomic size is too small s is updated
		return getVoid(start);
	}
	else{
		return getVoid(extend(size));
	}
}

int roundUp(int num, int mult){
	return num + mult - num % mult;
}

struct header* extend(size_t size){
	//Calculate allocation size
	size_t s;
	if(size < CHUNK/0x40)s = CHUNK;
	else if(size < CHUNK/0x4)s = roundUp(0x10 * size, CHUNK);
	else s = roundUp(0x4 * size, CHUNK);
	//Request
	void* allocated = request(s);
	//If size is smaller than ATTOMIC use that instead
	if(size < ATOMIC)size = ATOMIC;
	//If the allocated space is the same as the ATOMIC size
	//This should never happen with the given settings
	if(s!=ATOMIC){
		//Get the location for the free space
		add(
			offset((struct node*)allocated, size),
			size - s
		);
	}
	//Init header
	struct header* head = (struct header*)allocated;

	head->magic = MAGIC;
	head->size = size;
	return head;
}