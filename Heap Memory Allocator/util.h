#ifndef UTIL_H
#define UTIL_H
#include <stddef.h>

void* util_ptrAdd(void* ptr, size_t shift);
void* util_ptrSub(void* ptr, size_t shift);
#endif