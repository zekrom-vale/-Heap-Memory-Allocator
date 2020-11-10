/** 
 * Manages errors for the entire program
 * This will not always throw the error directly as some does common checking
 */

#include "error.h"

#define DBG true
void error(int err, char* fmt, ...){
	char* errStr[]={
		strerror(ENOMEM),
		"Corrupt Free Space",
		"Padding Overwirten",
		strerror(EINVAL),
		strerror(EFAULT)
	};
    m_error=err;
	fprintf(stderr, "Soemthing whent wrong: %s", errStr[err-1]);
	
	va_list list;
	va_start(list, fmt);
	fprintf(stderr, fmt, list);
	va_end(list);

    exit(err);
}

//#define E_NO_SPACE (1)
void error_noSpace(){
    error(E_NO_SPACE, "");
}

//#define E_CORRUPT_FREESPACE (2)
void error_freeSpace(struct node* cur){
    if(!linked_list_validate(cur))error(E_CORRUPT_FREESPACE, "");
}
    //#define E_PADDING_OVERWRITTEN (3)
void error_head(struct header* head){
	error_ptr(head);
	if(head->size<ATOMIC)
		error(
			E_BAD_POINTER,
			"Not atomic: size %uz",
			head->size
		);
	if(head->size%ALIGN!=0)
		error(
			E_BAD_POINTER,
			"Does not match with ALIGN(%d): %uz",
			ALIGN,
			head->size
		);
    if (head->magic != MAGIC)
		error(
			E_PADDING_OVERWRITTEN,
			"Invalid magic value, expected %d got %d",
			MAGIC,
			head->magic
		);
}
//#define E_BAD_ARGS (4)

void error_args(int size) {
  if (size <= 0 || size > MAX_SIZE)
    error(E_BAD_ARGS, "Bad size: %d ", size);
}

void error_args_t(size_t size) {
  if (size > MAX_SIZE)
    error(E_BAD_ARGS, "Bad size: %zu ", size);
}

//#define E_BAD_POINTER (5)
void error_ptr(void* ptr){
	if(LIST!=NULL && (void*)ptr<(void*)LIST)
		error(
			E_BAD_POINTER,
			"Address is before the start loction(%p) %p ",
			LIST,
			ptr
		);
	if((void*)ptr>(void*)(LIST->end))
		error(
			E_BAD_POINTER,
			"Address is after the end of the heap(%p): %p ",
			LIST->end,
			ptr
		);
	if((uintptr_t)ptr%ALIGN!=0)
		error(
			E_BAD_POINTER,
			"Address does not match with ALIGN(%d): %p",
			ALIGN,
			ptr
		);
}

void error_node(struct node* node){
	error_ptr(node);
	if(node->size<ATOMIC)
		error(
			E_BAD_POINTER,
			"Node is not at an atomic location %p ",
			node
		);
}