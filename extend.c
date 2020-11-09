/** 
 * Extends the program's memory space with mmap in defined chunks
 * This will be automaticaly called if EXTEND is true and the allocation service runs out of space
 */

#include "extend.h"

/**
 * requests a new chunk of memory
 * @param size the size of the block
 * @return the pointer of the start of the mmap
 */
void* extend_request(size_t size) {
  void* v =
      mmap(
		  NULL,
		  size,
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
  if (v == MAP_FAILED) {
    // perror("mmap");
    return NULL;
  }
  return v;
}

/**
 * Calculates the extended space
 * @param size the size to modify
 * @return the modified size
 */
size_t extend_calcSpace(size_t size) {
  if (size < CHUNK / 0x40) return CHUNK;
  if (size < CHUNK / 0x4) return util_roundUp(0x10 * size, CHUNK);
  return util_roundUp(0x4 * size, CHUNK);
}

#define BUFFER 0

/**
 * Extends the space by using mmap
 * @param size the size hint to expand by
 * @return the header of the expanded size
 */
struct header* extend_extend(size_t size) {
  size_t s = extend_calcSpace(size + BUFFER);

  // Request
  void* allocated = extend_request(s);

  if (allocated == NULL) error_noSpace();
  // If size is smaller than ATTOMIC use that instead
  if (size < ATOMIC) size = ATOMIC;
  // If the allocated space is the same as the ATOMIC size
  // This should never happen with the given settings
  if (s != ATOMIC) {
    // Get the location for the free space
    linked_list_add(list_find_offset((struct node*)allocated, size), s - size);
  }
  // Init header
  struct header* head = (struct header*)allocated;

  head->magic = MAGIC;
  head->size = size;
  return head;
}

/**
 * mmaps a new space for the start of the allocations
 * @param size the minimum size to expand
 * @return the header of the new mmaped space
 */
struct header* extend_extendInit(size_t size) {
  size_t s = util_roundUp(size + BUFFER + sizeof(struct linkedList), CHUNK);

  // Request
  struct linkedList* allocated = (struct linkedList*)extend_request(s);

  if (allocated == NULL) error_noSpace();
  init_list(allocated);
  linked_list_add(allocated + 1, s - sizeof(struct linkedList));
  return (struct header*)allocated;
}
