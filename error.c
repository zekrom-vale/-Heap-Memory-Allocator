/** 
 * Manages errors for the entire program
 * This will not always throw the error directly as some does common checking
 */

#include "error.h"

const char* errStr[]={
	"No Space Available",
	"Corrupt Free Space",
	"Padding Overwirten",
	"Bad Arguments",
	"Bad Pointer"
};

#define DBG true
error(int err){
    m_error=err;
	perror("Soemthing whent wrong: ");
	perror(errStr[err-1]);
    exit(err);
}

//#define E_NO_SPACE (1)
void error_noSpace(){
    error(E_NO_SPACE);
}

//#define E_CORRUPT_FREESPACE (2)
void error_freeSpace(struct node* cur){
    if(!linked_list_validate(cur))error(E_CORRUPT_FREESPACE);
}
    //#define E_PADDING_OVERWRITTEN (3)
void error_head(struct header* head){
	error_ptr(head);
	if(head->size<ATOMIC||head->size%ALIGN!=0)error(E_BAD_POINTER);
    if (head->magic != MAGIC){
        error(E_PADDING_OVERWRITTEN);
    }
}
//#define E_BAD_ARGS (4)

void error_args(int size) {
  if (size <= 0 || size > MAX_SIZE) {
    error(E_BAD_ARGS);
  }
}

void error_args_t(size_t size) {
  if (size > MAX_SIZE) {
    error(E_BAD_ARGS);
  }
}

//#define E_BAD_POINTER (5)
void error_ptr(void* ptr){
	if(
		LIST!=NULL
		&&
		ptr<LIST
		||
#if WSL
		&ptr<=ptr
#else
		sbrk(0)<ptr
#endif
		||
		(uintptr_t)ptr%ALIGN!=0
	)error(E_BAD_POINTER);
}

void error_node(struct node* node){
	error(node);
	if(node->size<ATOMIC)error(E_BAD_POINTER);
}