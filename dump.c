/** 
 * Manages printing of free spaces, linked list/params, and more
 */

#include "dump.h"

void* dump_loop(void* ptr){
	if(linked_list_validate(ptr)){
		struct node* n=ptr;
		linked_list_printNode(n);
		return util_ptrAdd(n, n->size);
	}
	struct header* head=ptr;
	if(alloc_validate(head)){
		alloc_printHeader(head);
		return util_ptrAdd(head, head->size);
	}
	//We lost it
	return NULL;
}

void dump_map(){
	for(
		void* cur=LIST+1;
		cur!=NULL;
		cur=dump_loop(cur)
	);
}

/** 
 * Dumps the linked list and nodes to stdout
 */
void dump_raw(){
	if (LIST == NULL) return;
	linked_list_printLinkedList();
	for(
		struct node* cur=LIST->first;
		cur!=NULL;
		cur=cur->next
	){
		linked_list_printNode(cur);
	}
    printf("\n");
}

void Mem_Dump(){
  dump_map();
}