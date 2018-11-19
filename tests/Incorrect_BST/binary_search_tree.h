
#include <stdio.h>
#include <stdlib.h>

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct node {
	struct node *right;
	struct node *left;
	int data;
} Node;

int insert(Node **root, int data);
Node *search(Node *root, int data);
Node *minNode(Node *root);
Node *deleteNode(Node **root, int data);
void inorder_traversal(Node *root);
#endif




