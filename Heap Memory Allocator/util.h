#ifndef __util_h__
#define __util_h__
#include <stddef.h>

void* util_ptrAdd(void* ptr, size_t shift);
void* util_ptrSub(void* ptr, size_t shift);
#endif