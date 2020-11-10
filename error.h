#ifndef ERROR_H
#define ERROR_H

#include "mem.h"
#include <stdlib.h>
#include <stdint.h>
#include "free.h"
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

struct node;
struct header;

void error_noSpace();

void error_freeSpace(struct node* cur);

void error_head(struct header* head);

void error_args(int size);
void error_args_t(size_t size);
void error_ptr(void* ptr);

#endif