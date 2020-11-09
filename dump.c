/** 
 * Manages printing of free spaces, linked list/params, and more
 */

#include "dump.h"

/**
 * Prints the current line
 * @param mod the current line % by 0x10
 * @param num the current line
 * @param line the string to print
 */
void dump_line(int mod, uintptr_t num , char line[]){
	if(mod == 0)printf(
		"\n0x%X%s\n   0 1 2 3 4 5 6 7 8 9 A B C D E F\n",
		num, //int div 16
		CLUSTER_STR
	);
	printf("%X %s\n", mod, line);
}

/**
 * The loop part of dump_map
 * @param mod 
 * @param str the current string
 * @param length the length of the free space
 * @param now the current address
 * @param p the long string to print dueing a full match
 * @param ps the short stiring to print during a paratl match
 * @return the new location
 */
uintptr_t dump_loop(
	int* mod, char str[], size_t length, uintptr_t now,
	char p[], char ps[]
){
	//Deal with starting chunks
  int sect = now % CLUSTER;
	if(*mod!=0x10){
		for(int j = 0x10-*mod; j >= 0; j--){
			strncat(str, ps, STR_SIZE);
		}
		dump_line(sect, now >> 4, str);
		strcpy(str, "");
	}
	sect = now % CLUSTER;

	//Deal with 0x10 chunks
	for(size_t i = length >> 4; i > 0; i--){
		*mod = length % 0x10;
		dump_line(sect, now >> 4, p);
		now += 0x10;
		length -= 0x10;
		sect = now % CLUSTER;
	}

	//Deal with excess length

	*mod = (int)length;
	for(int j = *mod; j >= 0; j--){
		strncat(str, ps, STR_SIZE);
	}
	//Not garentted to be under 0x10
	if(*mod == 0x10){
		dump_line(*mod,now >> 4,str);
		strcpy(str,""); //Clear string
	}

	return now + *mod;
}
/** 
 * Dumps the current memory map to stdout
 */
void dump_map(){
	if(LIST==NULL)return;
	linked_list_sort();
	struct node* cur = LIST->first;
	//List is the start of the 
	//uintptr_t start = (uintptr_t)LIST;
	char str[STR_SIZE];
	int mod=0x10;

	uintptr_t prev = (uintptr_t)cur / CLUSTER;
	while(cur!=NULL){
		size_t length = cur->size / CLUSTER;
		uintptr_t now = (uintptr_t)cur / CLUSTER;

		dump_loop(
			&mod, str, prev-now, prev,
			" x x x x x x x x x x x x x x x x", " x"
		);

		prev=dump_loop(
			&mod, str, length, now,
			" - - - - - - - - - - - - - - - -", " -"
		);
		cur=cur->next;
	}
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
  dump_raw();
	//dump_map();
}