#include "../../src/xmalloc.h"
#include "linked_list.h"
#include<stdlib.h>
#include<stdio.h>


void reverse(Node **list) {
	Node *prev = NULL;
	Node *current = *list;
	Node *next = NULL;
	while (current != NULL) {
		next = current->next;
		ptrcpy(&(current->next), prev);
		//current->next = prev;
		ptrcpy(&prev, current);
		ptrcpy(&current, next);
	}
	ptrcpy(list, prev);
}




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
		prepend(&list, &list, val);
		//ptrcpy(&list, newnode);
	}
	xmalloc_bp("LL created");
	traverse(list);
	reverse(&list);
	traverse(list);
	// printf("%p\n", list);
	// if  (list) {
	// 	printf("hereee%d\n", list->data);
	// }
}
