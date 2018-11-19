#include "doubly_linked_list.h"


Node *reverseK(Node *list, int k) {
	Node *curr = list;
	Node *next = NULL;
	Node *prev = NULL;
	int count = 0;
	while (curr != NULL && count < k) {
		ptrcpy(next, curr->next);
		ptrcpy(&(curr->next), prev);
		ptrcpy(&(curr->prev), NULL);
		if (prev) {
			ptrcpy(&(prev->prev), curr);
		}	
		ptrcpy(&prev, curr);
		ptrcpy(&curr, next); 
		count++;
	}

	if (curr) {
		ptrcpy(&(list->next), reverseK(curr, k));
		ptrcpy(&(list->next->prev), list);
	}

	return prev;

}



int main() {
	//Node *list = NULL;
	// list = prepend(list, 5);
	// list = prepend(list, 4);
	// list = prepend(list, 6);
	// list = append(list, 10);
	// list = prepend(list, 3);
	int xmalloc_stat = xmalloc_init();
	
	if(xmalloc_stat == -1){
		// failed to launch Flask server
		return(0);
	}


	int n;
	int k;
	printf("\nEnter number of data values: ");
	scanf("%d",&n);
	printf("\nEnter the values...\n");
	Node *list = NULL;
	int val;
	for(int i = 0; i < n; i++) {
		scanf("%d",&val);
		prepend(&list, &list, val);
	}
	printf("\n\nEnter the group size for reversal: ");
	scanf("%d", &k);
	traverse(list);
	xmalloc_bp("Before reversal");
	//ptrcpy(&list, reverseK(list, k));
	traverse(list);
	reverse_traverse(list);
}