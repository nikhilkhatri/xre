

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct node {
	struct node *next;
	int data;
} Node;

void create_node(Node **new_node, Node *next, int data);
Node *head(Node *list);
Node *next(Node *current);
int get_data(Node *entry);
Node *set_data(Node *entry, int data);
int index_of(Node *list, int data);
Node *get_tail(Node *list);
void prepend(Node **list, Node **new_node, int data);
void append(Node **list, Node **new_node, int data);
void traverse(Node *list);
int length(Node *list);
int isEmpty(Node *list);
void insert_at(Node **list, Node **new_node, int data, int index);

#endif

