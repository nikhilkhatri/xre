#include "doubly_linked_list.h"


int main() {
	//Node *list = NULL;
	// list = prepend(list, 5);
	// list = prepend(list, 4);
	// list = prepend(list, 6);
	// list = append(list, 10);
	// list = prepend(list, 3);
	xray_init("output.txt");
	int n;

	printf("\nEnter number of data values: ");
	scanf("%d",&n);
	printf("\nEnter the values...\n");
	Node *list = NULL;
	int val;
	for(int i = 0; i < n; i++) {
		scanf("%d",&val);
		ptrcpy(&list, prepend(list, val));
	}
	traverse(list);
	//list = deleteNodeAtGivenPos(list, 4);
	//list = deleteAllOccurences(list, 3);
	//traverse(list);
	//list = deleteNode(list, list->next->next);
	//reverse_traverse(list);
	// printf("%p\n", list);
	// if  (list) {
	// 	printf("hereee%d\n", list->data);
	// }
}

/*
int main() {
	/*Node *list = NULL; // = (Node *)malloc(sizeof(Node));
	int n,index,occur;
	printf("\nNumber of nodes in linked list: ");
	scanf("%d", &n);
	printf("\nEnter the value to stored in the nodes: ");
	for(int i = 0; i < n; i++) {
		int val;
		scanf("%d", &val);
		list = prepend(list, val);
		
	}
	traverse(list);
	
	//deleteNode(list,list->next->next); 
	printf("\nEnter index to be deleted - ");
	scanf("%d",&index);
 	//deleteNodeAtGivenPos(list, index);
 	traverse(list);
 	
 	printf("\nEnter number to be deleted - ");
 	scanf("%d",&occur);
 	//deleteAllOccur(list,occur);
	traverse(list);*/
	/*
	int index,occur;
	Node *list = NULL;
	list = prepend(list, 5);
	list = prepend(list, 4);
	list = append(list, 6);
	//list = append(list, 9);
	list = append(list, 7);
	list = append(list, 8);
	list = append(list, 9);
	list = append(list, 9);
	list = append(list, 10);
	list = append(list, 11);
	list = append(list, 9);
	
	

	traverse(list);
    list = deleteNode(list,list->next); 
    //traverse(list);
    
    printf("\nEnter index to be deleted - ");
	scanf("%d",&index);
 	deleteNodeAtGivenPos(list, index);
 	traverse(list);
 	
 	printf("\nEnter number to be deleted - ");
 	scanf("%d",&occur);
 	deleteAllOccurences(list,occur);
	traverse(list);
	
	
}*/
