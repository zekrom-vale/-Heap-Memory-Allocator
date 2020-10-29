#include "mem.h"

#define ALLOC_SIZE 0x3900
#define M_FREE true

int main(){
	Mem_Init(ALLOC_SIZE);
	void* a = Mem_Alloc(ALLOC_SIZE);
#if M_FREE
	Mem_Free(a);
#endif

	void* a1=Mem_Alloc(100);
	void* a2 = Mem_Alloc(200);
	void* a3 = Mem_Alloc(10);
	void* a4 = Mem_Alloc(2);

#if M_FREE
	Mem_Free(a3);
	Mem_Free(a1);
	Mem_Free(a2);
#endif
	a1=Mem_Alloc(310);
	a2 = Mem_Alloc(1);

	//Force it to expand memory
	a = Mem_Alloc(2 * ALLOC_SIZE);

	//This will destroy the allocator
	void* alc=Mem_Alloc(20);
	int* mangle = (int*)(alc + 21);
	//Writing over the free list
	*mangle = 678124523;
	//This will certainly be an unexpected result
	void* unknown = Mem_Alloc(20);
	//Malloc does not prevent this and adding support to support bad practice is not a good idea
}