#include "bt_to_dll.h"
#include "../../src/xmalloc.h"



int insert(Node **root, int data){
	if(*root == NULL){
		// create
		if (node_malloc(sizeof(Node), root)) {
			(*root)->data = data;
			(*root)->left = (*root)->right = NULL;
			return 0;
		}
		return -1;
	}

	if(data > (*root)->data) {
		return insert(&(*root)->right, data);
	}

	return insert(&(*root)->left, data);
}


void inorder_traversal(Node *root) {
	if (root == NULL) 
		return;
	inorder_traversal(root->left);
	printf("%d -> ", root->data);
	inorder_traversal(root->right);
}



void displayCList(Node *head) 
{ 
    printf("Circular Linked List is :\n"); 
    Node *itr;
    ptrcpy(&(itr), head); 
    do
    { 
        printf("%d", itr->data); 
        itr = itr->right; 
    } while (head!=itr); 
    printf("\n"); 
} 


Node* concatenate(Node *leftList, Node *rightList) {
	if (leftList == NULL) {
		return rightList;
	}

	if (rightList == NULL) {
		return leftList;
	}

	// Store last nodes of both lists
	Node **leftLast = &(leftList->left);
	Node **rightLast = &(rightList->left);

	// Connecting end of left list with beg of right list
	ptrcpy(&(*leftLast)->right, rightList);
	ptrcpy(&(*rightLast)->left, *leftLast);

	// Connecting end of right list with beg of left list
	ptrcpy(&leftList->left, rightLast);
	ptrcpy(&(*rightLast)->right, leftList);

	return leftList;
}

Node *bTreeToCList() {

}

int main() {
	int xmalloc_stat = xmalloc_init();
	
	if(xmalloc_stat == -1){
		// failed to launch Flask server
		return(0);
	}


	Node *root = NULL;
	int n;
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int data;
		scanf("%d", &data);
		insert(&root, data);	
	}
	inorder_traversal(root);
	printf("end\n");

}