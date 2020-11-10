/**
* Holds configuration options
*/

#include <stdbool.h>

/**
* If true coalesce the free space
*/
#define COALESCE true

/**
* Should we validdate the nodes?
* Not using this will cause crashes!!
*/
#define VALIDATE true

/**
* Should we create end nodes to allow for previous coalescing
*/
#define USE_END true

#include "linkedList.h"

#define LIST_HEAD sizeof(struct linkedList)

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
#define PAGE false

/**
* The magic value to validate headers
*/
#define MAGIC 0x144b36e8
/**
* The chunk of space to allocate at a time
* mmaped space will be rounded to this value
* Should be a factor of ALIGN
*/
#define CHUNK 0x4000UL
/**
* When true expand the mmaped space
*/
#define EXPAND true
/**
* The amount to align allocated space by
* Rounds up allocated space to this ammount
* Use 0x1 to disable
*/
#define ALIGN 0x8

/**
* The max size to allow for
* There is no point to allow for memory that is phicicaly imposible
*/
#define MAX_SIZE 0.01 * 1.074e9L

/** 
 * Is this Windows Subsystem for Luinx?
 * May be a dead flag
 */
#define WSL true

/** 
 * Is the Block to print different from align?
 */
#define BLOCK ALIGN

/** 
 * Should all the addresses in between be printed or just 8?
 * WARNING: Truning this on will create a lot of output
 */
#define PRINT_ALL false