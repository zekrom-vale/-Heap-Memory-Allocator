#include "mem.h"
#include "config.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NO_STDIO_REDIRECT

#define ALLOC_SIZE 0x3900
#define MM_FREE true

/**
 * Here we are allocating random sizes of memory
 * We start with the allocation max size and freeing that
 * Next we allocate 100, 200, 10, and 2000 byte multiples of mult
 * Freeing it in a a3 a1 a2 and a4, we test coalesce
 * Next it allocates a few more spaces that should not fit without coalesce
 * Then force it to expand memory by requesting 2x the size
 * Finaly free a1 and allocate a smaller size that will fit into the freed space
 * @param mult 
 */
void main_default(int mult){
	void* a = Mem_Alloc(ALLOC_SIZE);

#if MM_FREE
	Mem_Free(a);
	printf("Free a\n");
	Mem_Dump();
#endif

	void* a1=Mem_Alloc(100*mult);
	printf("Alloc 100 a1\n");
	Mem_Dump();

	void* a2 = Mem_Alloc(200*mult);
	printf("Alloc 200 a2\n");
	Mem_Dump();

	void* a3 = Mem_Alloc(10*mult);
	printf("Alloc 10 a3\n");
	Mem_Dump();

	void* a4 = Mem_Alloc(2000*mult);
	printf("Alloc 2000 a4\n");
	printf("Should only be one node\n");
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
	a1=Mem_Alloc(310*mult);
	printf("Alloc 310 a1\n");
	Mem_Dump();
	printf("Alloc 1 a2\n");
	a2 = Mem_Alloc(1*mult);
	Mem_Dump();

#if EXPAND
	//Force it to expand memory
	void* b = Mem_Alloc(2 * ALLOC_SIZE*mult);
	printf("Alloc 2ALLOC_SIZE a\n");
	Mem_Dump();
#endif

	printf("Free a1\n");
	Mem_Free(a1);
	Mem_Dump();

	printf("Alloc a1 250");
	a1 = Mem_Alloc(250);
	Mem_Dump();
}

/**
 * This is an extencive test for coalesce and reallocation
 * It will allocate random sizes of memory and randomly free a few
 * Next it allocates more that will not fit
 * @param mult 
 */
void main_small(int mult){
	void* a1=Mem_Alloc(12*mult);
	printf("Alloc 12 a1\n");
	Mem_Dump();

	void* a2 = Mem_Alloc(22*mult);
	printf("Alloc 22 a2\n");
	Mem_Dump();

	void* a3 = Mem_Alloc(20*mult);
	printf("Alloc 20 a3\n");
	Mem_Dump();

	void* a4 = Mem_Alloc(123*mult);
	printf("Alloc 123 a4\n");
	Mem_Dump();

	void* a5=Mem_Alloc(100*mult);
	printf("Alloc 100 a1\n");
	Mem_Dump();

	void* a6 = Mem_Alloc(200*mult);
	printf("Alloc 200 a2\n");
	Mem_Dump();

	void* a7 = Mem_Alloc(120*mult);
	printf("Alloc 120 a3\n");
	Mem_Dump();

	void* a8 = Mem_Alloc(20*mult);
	printf("Alloc 20 a4\n");
	Mem_Dump();

#if MM_FREE
	Mem_Free(a3);
	printf("Free a3\n");
	Mem_Dump();

	Mem_Free(a2);
	printf("Free a2\n");
	Mem_Dump();

	Mem_Free(a5);
	printf("Free a5\n");
	Mem_Dump();

	Mem_Free(a7);
	printf("Free a7\n");
	Mem_Dump();
#endif

	a2 = Mem_Alloc(232*mult);
	printf("Alloc 232 a2\n");
	Mem_Dump();

	a3 = Mem_Alloc(30*mult);
	printf("Alloc 30 a3\n");
	Mem_Dump();

#if MM_FREE
	Mem_Free(a3);
	printf("Free a3\n");
	Mem_Dump();

	Mem_Free(a2);
	printf("Free a2\n");
	Mem_Dump();

	Mem_Free(a1);
	printf("Free a3\n");
	Mem_Dump();

	Mem_Free(a8);
	printf("Free a2\n");
	Mem_Dump();

	Mem_Free(a6);
	printf("Free a5\n");
	Mem_Dump();

	Mem_Free(a4);
	printf("Free a7\n");
	Mem_Dump();

	Mem_Free(a5);
	printf("Free a5\n");
	Mem_Dump();

	Mem_Free(a7);
	printf("Free a7\n");
	Mem_Dump();
#endif
}

/** 
 * This breaks the allocator by setting a value in the free list
 * This should exit when trying to allocate more
 */
void main_break(){
	//This will destroy the allocator
	void* alc=Mem_Alloc(20);
	int* mangle = (int*)(alc + 21);
	//Writing over the free list
	*mangle = 678124523;
	//This will certainly be an unexpected result
	void* unknown = Mem_Alloc(20);
	//Malloc does not prevent this and adding support to support bad practice is not a good idea
}

/** 
 * Try to pass a negative value into Mem_Alloc
 * This will be rejected
 */
void main_breakNeg(){
	void* a=Mem_Alloc(-234);
}

/** 
* Try to pass a 0 into Mem_Alloc
* This will be rejected
*/
void main_breakZero(){
	void* a=Mem_Alloc(0);
}

/** 
* Try to free a pointer in the stack
* This is invalid as it must be a pointer returned by free
*/
void main_breakBad(){
	void* a=Mem_Alloc(2342);
	Mem_Free(&a);
}

/** 
 * Try to free a location ofset by 1 byte
 * If using ALIGN it will detect this invalid offset if not it will detect an invalid header
 */
void main_breakOffset(){
	void* a=Mem_Alloc(2342);
	Mem_Free((char*)a+1);
}

/** 
 * Try to free a NULL pointer
 * Thiss will be detected as a bad pointer
 */
void main_breakNULL(){
	Mem_Free(NULL);
}

/** 
 * Allocates and frees a memory location
 * Then frees the freed location
 * This shuld be dedtected as an invalid header
 */
void main_breakFree2(){
	void* a=Mem_Alloc(120);
	printf("Allocate a 120");
	Mem_Dump();

	printf("free a");
	Mem_Free(a);
	Mem_Dump();

	printf("Again!");
	Mem_Free(a);
}
 
int main(int argc, char* argv[]){
	Mem_Init(ALLOC_SIZE);
	printf("Init\n");
	Mem_Dump();
	if(argc<=1){
		main_default(1);
		return 0;
	}
	int mult;
	if(argc>=2)mult=argv[2];
	else mult=1;
	if(strcmp("default", argv[1]))main_default(mult);
	else if(strcmp("small", argv[1]))main_small(mult);
	else if(strcmp("break", argv[1]))main_break();
	else if(strcmp("breakNeg", argv[1]))main_breakNeg();
	else if(strcmp("breakZero", argv[1]))main_breakZero();
	else if(strcmp("breakBad", argv[1]))main_breakBad();
	else if(strcmp("breakNULL", argv[1]))main_breakNULL();
	else if(strcmp("breakOffset", argv[1]))main_breakOffset();
	else if(strcmp("breakFree2", argv[1]))main_breakFree2();
	else main_small(mult);
	return 0;
}
