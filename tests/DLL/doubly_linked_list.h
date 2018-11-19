#include <stdlib.h>
#include <stdio.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node { 
    int data; 
    struct node* next; // Pointer to next node in DLL 
    struct node* prev; // Pointer to previous node in DLL 
}Node;

void create_node(Node **new_node, Node *prev, Node *next, int data);
int isEmpty(Node *list);
void prepend(Node **list, Node **new_node, int data);
Node *append(Node *list, int data);
Node* deleteNode(Node *list, Node *del);
Node* deleteNodeAtGivenPos(Node *list, int index);
void traverse(Node *list);
void reverse_traverse(Node *list);
//Node* deleteAllOccurences(Node *list, int occur);
//void freelist(Node *list);

#endif
