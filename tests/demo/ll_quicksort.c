#include "../../src/xmalloc.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


Node *partition(Node *beg, Node *end, Node **new_head, Node **new_tail) {
	Node *current = beg;
	Node *tail = end;
	Node *pivot = tail;
	Node *prev = NULL;
	while (current != pivot) {
		if (current->data < pivot->data) {
			if (*new_head == NULL) {
				*new_head = current;
			}
			prev = current;
			current = next(current);
		}
		else {
			if (prev) {
				ptrcpy(&(prev->next), next(current));
			}
			Node *temp = next(current);
			ptrcpy(&(current->next), NULL);
			ptrcpy(&(tail->next), current);
			tail = current; //ptrcpy(&tail, tail->next); // ptrcpy(&tail, current)
			current = temp; // ptrcpy(&current, temp);
		}

	}

	if (*new_head == NULL) { // All elements are greater than pivot element
		*new_head = pivot; 
	}
	*new_tail = tail;
	traverse(*new_head);
	return pivot;
}

Node *quick_sort_recursive(Node *head, Node *tail) {
	if (!head || head == tail) {
		return head;
	}

	Node *new_head = NULL;
	Node *new_tail = NULL;

	Node *pivot = partition(head, tail, &new_head, &new_tail);

	if (new_head != pivot) {
		Node *temp = new_head;
		while (next(temp) != pivot) {
			temp = next(temp);
		}

		ptrcpy(&(temp->next), NULL);

		ptrcpy(&new_head, quick_sort_recursive(new_head, temp));

		Node *tail_node = get_tail(new_head);
		ptrcpy(&(tail_node->next), pivot);
	}

	ptrcpy(&(pivot->next), quick_sort_recursive(pivot->next, new_tail));
	return new_head;
}

Node *quick_sort(Node *head, Node *tail) {
	head = quick_sort_recursive(head, tail);
	//ptrcpy(&head, quick_sort_recursive(head, tail));
	return head;
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
		Node *newnode;
		prepend(&list, &list, val);
		printf("\nnode%d: %x\n", n-i ,&newnode);
	
		//ptrcpy(&list, newnode);
	}

	printf("\nUnsorted list: \n");
	traverse(list);
	printf("\nSorting the list...\n");
	list = quick_sort(list, get_tail(list));
	printf("\nSorted list: \n");
	traverse(list);
}
