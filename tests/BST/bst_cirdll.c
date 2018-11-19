#include "bst_cirdll.h"
#include "../../src/xmalloc.h"

Node *concatenate(Node *leftList, Node *rightList) 
{ 
    
    if (leftList == NULL) 
        return rightList; 
    if (rightList == NULL) 
        return leftList; 
    Node *leftLast ;
    ptrcpy(&(leftLast), leftList->left); 
    Node *rightLast ;
    ptrcpy(&(rightLast), rightList->left);
    ptrcpy(&(leftLast->right), rightList);
    ptrcpy(&(rightLast->right), rightList);  
    ptrcpy(&(leftList->left), rightLast);
    ptrcpy(&(rightLast->right), leftList);
  
    return leftList; 
} 
  

Node *bTreeToCList(Node *root) 
{ 
    if (root == NULL) 
        return NULL; 
  
    Node *left = bTreeToCList(root->left); 
    Node *right = bTreeToCList(root->right); 
    root->left = root->right = root; 
    return concatenate(concatenate(left, root), right); 
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
  

int insert(Node **root, int data){
	if(*root == NULL){
		
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

int main() 
{ 
    int xmalloc_stat = xmalloc_init();
    
    if(xmalloc_stat == -1){
        // failed to launch Flask server
        return(0);
    }

     //printf("1");
     Node *root = NULL;
	 int n;
	 printf("Enter number of nodes: ");
	 scanf("%d", &n);
	 for (int i = 0; i < n; i++) {
		int data;
		scanf("%d", &data);
		insert(&root, data);	
	 }
	
    bTreeToCList(root); 
   
    displayCList(root); 
    
    return 0; 
} 

