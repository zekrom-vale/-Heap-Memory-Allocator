#pragma once
struct node;
struct nodeEnd;
static const size_t END;
static const size_t ATOMIC;

struct node* offset(struct node* start,size_t size);
struct nodeEnd* getNodeEnd(struct node* start);
bool validate(struct node* start,struct nodeEnd* end);
struct node* getPrevNode(struct node* start);
struct linkedList;
static struct linkedList* LIST;
struct linkedList* init();
struct node* add(void* start,size_t size);
void remove(struct node* n);
void shift(struct node* start,size_t size);
void coalesce(struct node* start);
void* find(size_t* s);