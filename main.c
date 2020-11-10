#include "mem.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NO_STDIO_REDIRECT

#define ALLOC_SIZE 0x3900
#define MM_FREE true

int main(int argc, char* argv[]){
	Mem_Init(ALLOC_SIZE);
	printf("Init\n");
	Mem_Dump();
	if(argc<=1){
		main_default(1);
		return;
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
	else main_small(mult);
}

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

	//Force it to expand memory
	void* b = Mem_Alloc(2 * ALLOC_SIZE*mult);
	printf("Alloc 2ALLOC_SIZE a\n");
	Mem_Dump();
}

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

void main_breakNeg(){
	void* a=Mem_Alloc(-234);
}

void main_breakZero(){
	void* a=Mem_Alloc(0);
}

void main_breakBad(){
	void* a=Mem_Alloc(2342);
	Mem_Free(&a);
}

void main_breakNULL(){
	Mem_Free(NULL);
}