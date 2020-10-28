#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include "linkedList.h"
#include <string.h>
#include <stdint.h>

#define CLUSTER 0x100
#define CLUSTER_BYTES 3
#define CLUSTER_STR "000"
#define STR_SIZE 0x21

void dump_map();

#endif