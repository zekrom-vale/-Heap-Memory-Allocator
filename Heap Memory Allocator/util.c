#include "util.h"

void* ptrAdd(void* ptr, size_t shift){
	return (char*)ptr + shift;
}

void* ptrSub(void* ptr, size_t shift){
	return (char*)ptr - shift;
}