#include <stdio.h>
#include <unistd.h>
#include "../src/xmalloc.h"

/*
	This program tests the most basic functionality provided by xmalloc and xre
	It uses the struct given below nd creates a small arbitrary arrangement of instances of this.

	The sleep() call exists to ensure that log streaming
	to the front end takes place at the expected rate and there is no unexpected buffering
	
	This code must be paired with the streaming JavaScript client to see its working

	TBD:
		The python process currently just continues in the background, should this be killed?
		Should C wait for Flask, and then when SIGTERM hits, also kill Flask?
*/


typedef struct Node{
	struct Node *left;
	struct Node *right;
	int data;
	struct Node *rand;
} node;

int main(){

	int xmalloc_stat = xmalloc_init();
	
	if(xmalloc_stat == -1){
		// failed to launch Flask server
		return(0);
	}

	node *start;
	
	node_malloc(sizeof(node), (void **)&start);
	node_malloc(sizeof(node), (void **)&(start->left));
	// sleep(5);
	node_malloc(sizeof(node), (void **)&(start->right));
	// sleep(5);
	node_malloc(sizeof(node), (void **)&(start->rand));
	// sleep(10);
	node_malloc(sizeof(node), (void **)&(start->right->rand));

	node_malloc(sizeof(node), (void **)&(start->left->rand));

	ptrcpy(&(start->right->rand), start->left->rand);
	// sleep(5);
	// xmalloc_free((void *)(start->right));
	// xmalloc_free((void *)(start->right->rand->rand));

	// ptrcpy(&(start->right), start->left);

	return 0;
}
