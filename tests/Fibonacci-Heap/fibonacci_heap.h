#include <stdio.h>
#include <stdlib.h>

#ifndef FIB_HEAP_H
#define FIB_HEAP_H

typedef struct fib_heap_node {
	struct fib_heap_node *parent;
	struct fib_heap_node *right;
	struct fib_heap_node *left;
	struct fib_heap_node *child;
	int degree;
	int marked;
	int data;

} Node;

typedef struct fib_heap {
	Node *min;
	int node_count;
} Heap;


#define FALSE 0
#define TRUE 1

void make_fib_heap(Heap **H);
void insert(Heap **H, Node **x);

#endif