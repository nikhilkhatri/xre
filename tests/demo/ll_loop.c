#include "../../src/xmalloc.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>



Node *detect_and_remove_loop(Node *list) {
	if (list == NULL || list->next == NULL) {
		return list;
	}
	Node *slow = next(list);
	Node *fast = next(next(list));

	while (fast && next(fast)) {
		// xmalloc_bp("Iterating");
		if (slow == fast) {
			break;
		}
		slow = next(slow);
		fast = next(next(fast));
	}

	if (slow == fast) {
		slow = list;
		while (next(slow) != next(fast)) {
			slow = next(slow);
			fast = next(fast);
		}
		ptrcpy(&(fast->next), NULL);
	}
	return list;
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
	int val;
	for(int i = 0; i < n; i++) {
		scanf("%d",&val);
		prepend(&list,&list, val);
	}

	// create a loop between a randomly picked node and the last node
	int k = rand() % (n + 1) + 1;
	printf("k: %d\n", k);
	Node *end = list;
	while (--k) {
		end = next(end);
	}
	
	traverse(list);
	Node *beg = get_tail(list);
	xmalloc_bp("Before loop");
	ptrcpy(&(beg->next), end);
	xmalloc_bp("Add loop");
	list = detect_and_remove_loop(list);
	xmalloc_bp("Remove loop");
	traverse(list);
}