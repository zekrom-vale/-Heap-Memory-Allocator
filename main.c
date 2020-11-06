#include "mem.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

#define ALLOC_SIZE 0x3900
#define MM_FREE true
#define BREAK false

int main(){
	Mem_Init(ALLOC_SIZE);
	printf("Init\n");
	Mem_Dump();
	void* a;
#if false
	a = Mem_Alloc(ALLOC_SIZE);

#if MM_FREE
	Mem_Free(a);
	printf("Free a\n");
	Mem_Dump();
#endif
#endif

	void* a1=Mem_Alloc(100);
	printf("Alloc 100 a1\n");
	Mem_Dump();
	
	void* a2 = Mem_Alloc(200);
	printf("Alloc 200 a2\n");
	Mem_Dump();
	
	void* a3 = Mem_Alloc(10);
	printf("Alloc 10 a3\n");
	Mem_Dump();

	void* a4 = Mem_Alloc(2000);
	printf("Alloc 2000 a4\n");
	Mem_Dump();

#if MM_FREE
	Mem_Free(a3);
	printf("Free a3\n");
	Mem_Dump();

	Mem_Free(a1);
	printf("Free a1\n");
	Mem_Dump();
	
	Mem_Free(a2);
	printf("Free a2\n");
	Mem_Dump();

	
	Mem_Free(a4);
	printf("Free a4\n");
	Mem_Dump();
#endif
	a1=Mem_Alloc(310);
	printf("Alloc 310 a1\n");
	Mem_Dump();
	printf("Alloc 1 a2\n");
	a2 = Mem_Alloc(1);
	Mem_Dump();

	//Force it to expand memory
	a = Mem_Alloc(2 * ALLOC_SIZE);
	printf("Alloc 2ALLOC_SIZE a\n");
	Mem_Dump();

#if BREAK
	//This will destroy the allocator
	void* alc=Mem_Alloc(20);
	int* mangle = (int*)(alc + 21);
	//Writing over the free list
	*mangle = 678124523;
	//This will certainly be an unexpected result
	void* unknown = Mem_Alloc(20);
	//Malloc does not prevent this and adding support to support bad practice is not a good idea
#endif
}
