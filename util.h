#ifndef UTIL_H
#define UTIL_H
#include <stddef.h>

void* util_ptrAdd(void* ptr, size_t shift);
void* util_ptrSub(void* ptr, size_t shift);
int util_roundUp(int num, int mult);
size_t util_roundUp_t(size_t num, size_t mult);
#endif
