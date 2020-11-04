#ifndef ERROR_H
#define ERROR_H

#include "free.h"
#include "mem.h"
#include "stdlib.h"

/**
 * The max size to allow for
 * There is no point to allow for memory that is phicicaly imposible
 */
#define MAX_SIZE 0.01 * 1.074e9L

void error_noSpace();

void error_freeSpace(struct node* cur);

void error_head(struct header* head);

void error_args(int size);
void error_args_t(size_t size);

#endif