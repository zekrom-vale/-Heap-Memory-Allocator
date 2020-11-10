/** 
 * This file alocates chunks of memory to the user
 */

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
	size_t s = util_roundUp_t(
	  (size_t)size + sizeof(struct header),
	  ALIGN
	);
	void* start=list_find(&s);
	if(start!=NULL){
		struct header* head=start;
		head->magic=MAGIC;
		head->size=s; //If atomic size is too small s is updated
		return alloc_getVoid(start);
	}
	else{
		#if EXPAND
		return alloc_getVoid(extend_extend(s));
		#else
			error_noSpace();
		#endif
	}
}

#include <stdio.h>
void alloc_printHeader(struct header* head){
	printf(
		"struct header* %p=[size=%zu]\n",
		head,
		head->size
	);
}

void alloc_printHeaderAlt(struct header* head){
	printf("Header\n");
	printf("%p <-- Magic %d\n", &(head->magic), head->magic);
	printf("%p <-- Size %zu\n", &(head->size), head->size);
}

void alloc_printSection(void* ptr, char* txt){
	printf("%p %s\n", ptr, txt);
}

void alloc_printHeaderMore(struct header* head){
	alloc_printHeaderAlt(head);
	alloc_printSection(head+1, "<-- Allocated space start");
	if(PRINT_ALL||head->size<=BLOCK*8){
		for(size_t o=BLOCK; o<=head->size-BLOCK; o+=BLOCK){
			alloc_printSection(
				util_ptrAdd(head+1, o),
				""
			);
		}
	}
	else{
		for(size_t o=BLOCK; o<=BLOCK*4; o+=BLOCK){
			alloc_printSection(
				util_ptrAdd(head+1, o),
				""
			);
		}
		printf(".\n.\n.\n");
		for(size_t o=head->size-BLOCK*4; o<=head->size-BLOCK; o+=BLOCK){
			alloc_printSection(
				util_ptrAdd(head+1, o),
				""
			);
		}
	}
	alloc_printSection(
		util_ptrAdd(head+1, head->size),
		"<-- Allocated space end"
	);
}

bool alloc_validate(struct header* head){
	if(head==NULL||head<LIST||head>=LIST->end)return false;
	return head->magic==MAGIC;
}