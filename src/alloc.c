
#include "linkedList.c"
#include "init.c"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define MAGIC 0x144b36e8

struct header{
	int magic;
	size_t size;
}

const static size_t HEADER_SIZE=sizeof(struct header);

//|h|h|h|h|x|x|x|x|x|x|x|
/**
*Returns the starting location of the space
*@param start the location of the heaer
*/
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

void* extend(size_t size){
	return Mem_Init((int)size);
}
