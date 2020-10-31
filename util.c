#include "util.h"

void* util_ptrAdd(void* ptr, size_t shift){
	return (char*)ptr + shift;
}

void* util_ptrSub(void* ptr, size_t shift){
	return (char*)ptr - shift;
}

int util_roundUp(int num, int mult){
	return num + mult - num % mult;
}

size_t util_roundUp_t(size_t num, size_t mult){
	return num + mult - num % mult;
}