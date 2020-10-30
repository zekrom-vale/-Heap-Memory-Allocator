#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include "linkedList.h"
#include <string.h>
#include <stdint.h>

#define CLUSTER_BYTES 1
#define CLUSTER 32 << CLUSTER_BYTES
#define CLUSTER_STR "0"
#define STR_SIZE 0x21

void dump_map();

#endif