#include "binary_search_tree.h"
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


Node *search(Node *root, int data) {
	if (root == NULL || root->data == data) {
		return root;
	}

	if (data < root->data) {
		return search(root->left, data);
	}

	return search(root->right, data);
}


Node *minNode(Node *root) {
	Node *curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	return curr;
}


Node *deleteNode(Node **root, int data) {
	if (*root == NULL) {
		return *root;
	}

	if (data < (*root)->data) {
		ptrcpy(&(*root)->left, deleteNode(&(*root)->left, data));
	}

	else if (data > (*root)->data) {
		ptrcpy(&(*root)->right, deleteNode(&(*root)->right, data));
	}

	else {
		if ((*root)->left == NULL) {
			Node *temp = (*root)->right;
			xmalloc_free(*root);
			return temp;
		}

		if ((*root)->right == NULL) {
			Node *temp = (*root)->left;
			xmalloc_free(*root);
			return temp;
		}

		Node *temp = minNode((*root)->right);

		(*root)->data = temp->data;
		ptrcpy(&(*root)->right, deleteNode(&(*root)->right, temp->data));

	}

      return *root;
}

void inorder_traversal(Node *root) {
	if (root == NULL) 
		return;
	inorder_traversal(root->left);
	printf("%d -> ", root->data);
	inorder_traversal(root->right);
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
	deleteNode(&root, 70);
	inorder_traversal(root);
	printf("end\n");
	
}

