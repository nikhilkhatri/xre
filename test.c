#include <stdio.h>
#include "xmalloc.h"

typedef struct Node{
	struct Node *left;
	struct Node *right;
	int data;
	struct Node *rand;
} node;

int main(){

	xmalloc_init("logs_1.txt");
	
	node *start;
	
	node_malloc(sizeof(node), (void **)&start);
	node_malloc(sizeof(node), (void **)&(start->left));
	node_malloc(sizeof(node), (void **)&(start->right));
	
	node_malloc(sizeof(node), (void **)&(start->right->rand));
	node_malloc(sizeof(node), (void **)&(start->right->rand->rand));
	
	xmalloc_free((void *)(start->right));
	xmalloc_free((void *)(start->right->rand->rand));

	ptrcpy(&(start->right), start->left);

	return 0;
}


// dest -> start -> newloc


// int insert(node **proot, int data){
// 	if(*proot == NULL){
// 		// create
// 		if (node_malloc(sizeof(node), proot)) {
// 			*proot->data = data;
// 			*proot->left = *proot->right = NULL;
// 			return 0;
// 		}
// 		return -1;
// 	}

// 	if(data > *proot->data) {
// 		return insert(&(*proot->right), data);
// 	}

// 	return insert(&(*proot->left), data);
// }

