#include "dump.h"

void dump_line(int mod, uintptr_t num , char line[]){
	if(mod == 0)printf(
		"\n0x%X%s\n   0 1 2 3 4 5 6 7 8 9 A B C D E F\n",
		num, //int div 16
		CLUSTER_STR
	);
	printf("%X %s\n", mod, line);
}

uintptr_t dump_loop(
	int* mod, char str[], size_t length, uintptr_t now,
	char p[], char ps[]
){
	//Deal with starting chunks
	int sect = now % 0x100;
	if(mod!=0x10){
		for(int j = 0x10-*mod; j >= 0; j--){
			strncat(str, ps, STR_SIZE);
		}
		dump_line(sect, now >> 4, str);
		strcpy(str, "");
	}
	sect = now % 0x100;

	//Deal with 0x10 chunks
	for(int i = length >> 4; i > 0; i--){
		*mod = length % 0x10;
		dump_line(sect, now >> 4, p);
		now += 0x10;
		length -= 0x10;
		sect = now % 0x100;
	}

	//Deal with excess length

	*mod = length;
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

		if(prev!=now&&mod!=0x10){
			//Small offset
		}

		dump_loop(
			&mod, str, prev-now, prev,
			" x x x x x x x x x x x x x x x x", " x"
		);

		prev=dump_loop(
			&mod, str, length, now,
			" - - - - - - - - - - - - - - - -", " -"
		);
	}
}