#include "listFind.h"

/**
 * Finds the next space avalbe
 * @param s the size to find, updated if remaning space is not attomic
 * @return a pointer to the allocated space, NULL if not found (Does not expand
 * memory)
 */
void* list_find(size_t* s) {
	switch (LIST->MODE) {
		case FIRSTFIT:
			return list_find_findFirstFit(s);
		case BESTFIT:
			return list_find_findBestFit(s);
		case WORSTFIT:
			return list_find_findWorstFit(s);
	}
	return NULL;
}

void* list_find_process(size_t* s, struct node* start) {
	if (start->size < *s) {
		// Failure space is too small
		return NULL;
	}
	// If the remaning space is not attomic allocate more and update s
	size_t min = *s + ATOMIC;
	if (start->size - *s < min) {
		*s = min;
		linked_list_remove(start);
	}
	// Otherwise just sift it
	else {
		if (*s < ATOMIC) *s = ATOMIC;
		linked_list_shift(start, *s);
	}
	// Return the location of the space
	return start;
}

/**
 * Finds the first fit for the requested space
 * This finds the first valid space
 * @param s the size of the requested space
 * @return the location of the first fit, if not NULL
 */
void* list_find_findFirstFit(size_t* s) {
	struct node* cur = LIST->first;
	size_t size = *s;
	while (cur != NULL) {
		error_freeSpace(cur);
		// If the size is larger than requested
		if (cur->size >= size) {
			// If a perfect match
			if (cur->size == size) {
				linked_list_remove(cur);
				return cur;
			}
			return list_find_process(s, cur);
		}
		cur = cur->next;
	}
	// Failure
	return NULL;
}

/**
 * Finds the wost fit for the requested space
 * This finds the largest space
 * @param s the size of the requested space
 * @return the location of the wost fit, if not NULL
 */
void* list_find_findWorstFit(size_t* s) {
	struct node* cur = LIST->first;
	struct node* large = cur;
	size_t size = *s;
	while (cur != NULL) {
		error_freeSpace(cur);
		// If the size is larger than requested
		if (cur->size >= size) {
			// If a perfect match
			if (cur->size == size) {
				linked_list_remove(cur);
				return cur;
			}
			// If cur is larger replace large
			if (cur->size > large->size) large = cur;
		}
		cur = cur->next;
	}
	return list_find_process(s, large);
}

/**
 * Finds the wost best for the requested space
 * This finds the smallest space
 * @param s the size of the requested space
 * @return the location of the best fit, if not NULL
 */
void* list_find_findBestFit(size_t* s) {
	struct node* cur = LIST->first;
	struct node* small = cur;
	size_t size = *s;
	while (cur != NULL) {
		error_freeSpace(cur);
		// If the size is larger than requested
		if (cur->size >= size) {
			// If a perfect match
			if (cur->size == size) {
				linked_list_remove(cur);
				return cur;
			}
			// If cur is larger replace small
			if (cur->size > size && cur->size < small->size) small = cur;
		}
		cur = cur->next;
	}
	return list_find_process(s, small);
}

/**
 * gets the next location of the node
 * @param start the original node
 * @param size the offset
 */
struct node* list_find_offset(struct node* start, size_t size) {
	assert(size >= ATOMIC);
	struct node* next = (struct node*)util_ptrAdd(start, size + 1);
	return next;
}

#if USE_END
/**
 *returns the location of the end of the node
 *@param start the node to get the end of
 */
struct nodeEnd* list_find_getNodeEnd(struct node* start) {
	return (struct nodeEnd*)util_ptrAdd(start, start->size - END);
	//|x|x|x|x|x|x|x|x|x| | | | | | | | | | | | |e|e|e|e| |
	// 0								 1
	// 2 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
}

/**
 * Returns the next node
 * @param cur the current node
 * @return the next node
 */
struct node* list_find_getNextNode(struct node* cur) {
	return util_ptrAdd(cur->end + 1, 1);
}

/**
 * Return the previous node if valid, NULL if not
 * @param start the current noe
 * @return The previous node, NULL if invalid
 */
struct node* list_find_getPrevNode(struct node* start) {
	struct nodeEnd* end = util_ptrSub((struct nodeEnd*)start - 1, 1);
	if (linked_list_validateEnd(end)) return end->start;
	return NULL;
}
#endif
