#include "../../src/xmalloc.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/*
typedef struct node {
	struct node *next;
	int data;
} Node;
*/


void create_node(Node **new_node, Node *next, int data) {
	node_malloc(sizeof(Node), new_node);
	if (*new_node) {
		ptrcpy(&(*new_node)->next, next);
		(*new_node)->data = data;
	}
}


Node *head(Node *list) {
	return list;
}

Node *next(Node *current) {
	return current ? current->next : NULL;
}

int get_data(Node *entry) {
	return entry ? -1 : entry->data;
}

Node *set_data(Node *entry, int data) {
	if (entry) {
		entry->data = data; // how to reflect change in frontend
	}
	return entry;
}

int index_of(Node *list, int data) {
	Node *temp = list;
	for (int i = 0; temp != NULL; temp = next(temp), i++) {
		if (temp->data == data) {
			return i;
		}
	}
	return -1;
}

Node *get_tail(Node *list) {
	Node *tail_node = list;
	while (tail_node && next(tail_node)) {
		tail_node = next(tail_node);
	}

	return tail_node;
}


void prepend(Node **list, Node **new_node, int data) {
	create_node(new_node, *list, data);
	//printf("%p\n", new_node);
}


void append(Node **list, Node **new_node, int data) {
	//Node *new_node;
	create_node(new_node, NULL, data);
	if (*new_node == NULL) {
		return;
	}

	if (*list == NULL) {
		ptrcpy(list, *new_node);
		printf("first %x %x\n", *list, (*list)->next);
		return;
	}

	Node **temp = list;
	printf("first %x %x\n", *list, (*list)->next);

	while (*temp != NULL && (*temp)->next != NULL) {
		//ptrcpy(&temp, temp->next);
		printf("here %x %x\n", *temp, (*temp)->next);
		temp = &((*temp)->next);
	}
	ptrcpy(&(*temp)->next, *new_node);
	//temp->next = new_node;
	//return list;
}

void traverse(Node *list) {
	Node *temp;
	ptrcpy(&temp, list);	
	while (temp) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	} 
	printf("end\n");
}


int length(Node *list) {
	if (list == NULL) {
		return 0;
	}
	return 1 + length(list->next);
}

int isEmpty(Node *list) {
	return list == NULL;
}

void insert_at(Node **list, Node **new_node, int data, int index)
{
	//Node *new_node = create_node(NULL, data);
	//Node *new_node;
	create_node(new_node, NULL, data);
	if (*new_node == NULL || *list == NULL) {
		return ;
	}
	Node *temp = *list;
	for(int i = 0; i < index; i++) {
		//ptrcpy(&temp, next(temp));
		temp = temp->next;
	}
	ptrcpy(&(*new_node)->next, temp->next);
	ptrcpy(&(temp->next), *new_node);
}

/*
int main() {
	int xmalloc_stat = xmalloc_init();
	
	if(xmalloc_stat == -1){
		// failed to launch Flask server
		return(0);
	}

	
	int n;

	printf("\nEnter number of data values: ");
	scanf("%d",&n);
	printf("\nEnter the values...\n");
	Node *list = NULL;

	printf("list: %x\n", &list);
	int val;
	for(int i = 0; i < n; i++) {
		scanf("%d",&val);
		Node *newnode;
		append(&list, &newnode, val);
		printf("\nnode%d: %x\n", n-i ,&newnode);
		
		//ptrcpy(&list, newnode);
	}
	traverse(list);
	
}
*/