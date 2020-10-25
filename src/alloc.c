
#include "linkedList.c"
#define MAGIC 0x144b36e8

struct header{
	int magic;
	size_t size;
}

const static size_t HEADER_SIZE=sizeof(struct header);

//|h|h|h|h|x|x|x|x|x|x|x|
struct header* getHead(void* start){
	return (struct header*)(start-HEADER_SIZE);
}

void* getVoid(void* start){
	return start+HEADER_SIZE;
}

void* Mem_Alloc(int size){
	size_t s=(size_t)size+HEADER_SIZE;
	void* start=find(s);
	if(start!=NULL){
		struct header* head=(struct header*)start;
		head->magic=MAGIC;
		head->size=s; //If atomic size is too small s is updated
		return getVoid(start);
	}
	else{
		//Allocate
	}
}
