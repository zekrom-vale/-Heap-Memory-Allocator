#include "util.h"

void* util_ptrAdd(void* ptr, size_t shift){
	return (char*)ptr + shift;
}

void* util_ptrSub(void* ptr, size_t shift){
	return (char*)ptr - shift;
}