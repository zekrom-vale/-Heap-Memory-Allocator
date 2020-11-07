#include "util.h"

/**
 * Adds a pointer and an offset
 * @param ptr the pointer to add
 * @param shift the offset to add
 * @return the new void* pointer
 */
void* util_ptrAdd(void* ptr, size_t shift){
	return (char*)ptr + shift;
}

/**
 * Subtracts a pointer and an offset
 * @param ptr the pointer to subtract from
 * @param shift the offset to subtract
 * @return the new void* pointer
 */
void* util_ptrSub(void* ptr, size_t shift){
	return (char*)ptr - shift;
}

/**
 * Rounds up ints by a multiple
 * @param num the int to round
 * @param mult the multiple to round by
 * @return the rounded int
 */
int util_roundUp(int num, int mult){
	return num + mult - num % mult;
}

/**
 * Rounds up size_t by a multiple
 * @param num the size_t to round
 * @param mult the multiple to round by
 * @return the rounded size_t
 */
size_t util_roundUp_t(size_t num, size_t mult){
	return num + mult - num % mult;
}