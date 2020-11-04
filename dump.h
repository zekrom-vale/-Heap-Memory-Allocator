#ifndef DUMP_H
#define DUMP_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define CLUSTER_BYTES 1
#define CLUSTER 32 << CLUSTER_BYTES
#define CLUSTER_STR "0"
#define STR_SIZE 0x21

void dump_map();

#endif
