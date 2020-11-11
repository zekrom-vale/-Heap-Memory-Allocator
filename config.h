/**
* Holds configuration options
*/

#include <stdbool.h>

/**
* If true coalesce the free space
*/
#ifndef COALESCE
#define COALESCE true
#endif

/**
* Should we validdate the nodes?
* Not using this will cause crashes!!
*/
#ifndef VALIDATE
#define VALIDATE true
#endif

/**
* Should we create end nodes to allow for previous coalescing
*/
#ifndef USE_END
#define USE_END true
#endif

#include "linkedList.h"

#ifndef LIST_HEAD
#define LIST_HEAD sizeof(struct linkedList)
#endif

#if USE_END
/**
*The size of the end node
*/

#define END sizeof(struct nodeEnd)

/**
*The absolute minumum of the free space
*It is posible to allocate if the size is the same as struct node, but that
* requres more logic
*/
#define ATOMIC sizeof(struct node) + sizeof(struct nodeEnd)
#else
#define ATOMIC 1 * sizeof(struct node)
#endif


/**
* If true pass the page size to mmap, 0 otherwise
*/
#ifndef PAGE
#define PAGE false
#endif

/**
* The magic value to validate headers
*/
#ifndef MAGIC
#define MAGIC 0x144b36e8
#endif
/**
* The chunk of space to allocate at a time
* mmaped space will be rounded to this value
* Should be a factor of ALIGN
*/
#ifndef CHUNK
#define CHUNK 0x4000UL
#endif
/**
* When true expand the mmaped space
*/
#ifndef EXPAND
#define EXPAND false
#endif
/**
* The amount to align allocated space by
* Rounds up allocated space to this ammount
* Use 0x1 to disable
*/
#ifndef ALIGN
#define ALIGN 0x8
#endif
/**
* The max size to allow for
* There is no point to allow for memory that is phicicaly imposible
*/
#ifndef MAX_SIZE
#define MAX_SIZE 0.01 * 1.074e9L
#endif
/** 
 * Is this Windows Subsystem for Luinx?
 * May be a dead flag
 */
#ifndef WSL
#define WSL true
#endif
/** 
 * Is the Block to print different from align?
 */
#ifndef BLOCK
#define BLOCK ALIGN
#endif
/** 
 * Should all the addresses in between be printed or just 8?
 * WARNING: Truning this on will create a lot of output
 */
#ifndef PRINT_ALL
#define PRINT_ALL false
#endif