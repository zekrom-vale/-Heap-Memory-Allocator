#include "extend.h"

/**
 * Creates and attatches a new frame to keep track of the allocated space
 * @param start the mmaped address
 * @param size the size of the frame
 * This will be updated to the free space size so you need to pass a pointer (&size)
 * @return the start of te free space
 */
void* extend_addFrame(void* start, size_t* size){
	struct frame* head=start;
	struct node* n;
	if(LIST==NULL){
		struct linkedList* list=init_list(head+1);
		n=list+1;
	}
	else{
		n=start+1;
	}
	if(LIST->firstFrame==NULL){
		LIST->firstFrame=head;
	}
	else{
		struct frame* prev=LIST->lastFrame;
		//If the frames are next to eachother
		if(util_ptrAdd(prev, prev->size)==head){
			//coalece frames
			prev->size+=*size;
			n=linked_list_add(n, *size);
			*size=0;
#if COALESCE
			return linked_list_coalesce(n);
#endif
			return start;
		}
		prev->next=head;
	}
	head->size=*size;
	head->next=NULL;
	LIST->lastFrame=head;
	//Update the size
	*size=*size-sizeof(struct frame);
	//Shift by one frame to get the free space
	return n+1;
}

/**
 * requests a new chunk of memory
 * @param size the size of the block
 * @return the pointer of the start of the mmap
 */
void* extend_request(size_t* size) {
	void* v =
			mmap(NULL, *size,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS,
			// Don't need file device (fd) with MAP_ANONYMOUS
			0,
#if PAGE
			sysconf(_SC_PAGE_SIZE)
#else
			0
#endif
			);
	if (v == MAP_FAILED){
		error_noSpace();
	}
#if USE_FRAME
	v=extend_addFrame(v, size);
#endif
	return v;
}

#define BUFFER 0
/**
 * Calculates the extended space
 * @param size the size to modify
 * @return the modified size
 */
size_t extend_calcSpace(size_t size){
#if BUFFER!=0
	size+=BUFFER;
#endif
#if USE_FRAME
	size+=sizeof(struct frame);
#endif
	if (size < CHUNK / 0x40) return CHUNK;
	if (size < CHUNK / 0x4) return util_roundUp(0x10 * size, CHUNK);
	return util_roundUp(0x4 * size, CHUNK);
}


/**
 * Extends the space by using mmap
 * @param size the size hint to expand by
 * @return the header of the expanded size
 */
struct header* extend_extend(size_t requestedSize) {
	size_t extendedSize = extend_calcSpace(requestedSize);

	// Request
	void* allocated = extend_request(&extendedSize);
#if USE_FRAME
	if (extendedSize == 0){
        linked_list_add(
			allocated,
			extendedSize
			- sizeof(struct linkedList)
		);
		linked_list_shift(allocated, requestedSize);
		return alloc_core(allocated, requestedSize);
	}
#endif
	// If size is smaller than ATTOMIC use that instead
	if (requestedSize < ATOMIC) requestedSize = ATOMIC;
	// If the allocated space is the same as the ATOMIC size
	// This should never happen with the given settings
	if (extendedSize != ATOMIC) {
		// Get the location for the free space
		linked_list_add(
			list_find_offset((struct node*)allocated, requestedSize),
			extendedSize - requestedSize
		);
	}
	// Init header
	struct header* head = (struct header*)allocated;

	head->magic = MAGIC;
	head->size = requestedSize;
	return head;
}

/**
 * mmaps a new space for the start of the allocations
 * @param size the minimum size to expand
 * @return the header of the new mmaped space
 */
struct header* extend_extendInit(size_t size) {
	size_t s = util_roundUp(
		size+
		sizeof(struct linkedList)
#if USE_FRAME
		+
		sizeof(struct frame)
#endif
		,
		CHUNK
	);

	// Request
	struct linkedList* allocated = (struct linkedList*)extend_request(&s);

#if USE_FRAME
        linked_list_add(
			allocated,
			s - sizeof(struct frame) -
			sizeof(struct linkedList)
		);
        linked_list_shift(allocated, size);
        return alloc_core(allocated, size);
#endif

	if (allocated == NULL) error_noSpace();
	init_list(allocated);
	linked_list_add(allocated + 1, s - sizeof(struct linkedList));
	return (struct header*)allocated;
}
