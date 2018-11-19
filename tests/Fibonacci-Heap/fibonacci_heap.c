#include "fibonacci_heap.h"
#include "../../src/xmalloc.h"


void make_fib_heap(Heap **H) {
	node_malloc(sizeof(Heap), H);
	if (*H) {
		(*H)->node_count = 0;
		(*H)->min = NULL;
	} 
}

void create_and_insert(Heap **H, Node **x, int data) {
	create_node(x, data);
	insert(H, x);
}

void create_node(Node **x, int data) {
	node_malloc(sizeof(Node), x);
	if (*x) {
		(*x)->degree = 0;
		(*x)->data = data;
		(*x)->marked = FALSE;
		(*x)->parent = NULL;
		(*x)->child = NULL;
		(*x)->left = NULL;
		(*x)->right = NULL;

	}
}

void insert(Heap **H, Node **x) {
	if ( (*H)->min == NULL ) {				// Heap has 0 nodes
		ptrcpy(&(*x)->right, *x);
		ptrcpy(&(*x)->left, *x);
		ptrcpy(&(*H)->min, *x);
	}
	else {
		Node **min = &(*H)->min;
		Node **left = &(*min)->left;
		if (left == *min) {					// Heap has 1 node
			ptrcpy(&(*min)->right, *x);
			ptrcpy(&(*x)->left, *min);
		} 
		else {								// Heap has more than 1 node
			ptrcpy(&(*left)->right, *x);
			ptrcpy(&(*x)->left, *left);	
		}
		ptrcpy(&(*min)->left, *x);
		ptrcpy(&(*x)->right, *min);
		if ((*min)->data > (*x)->data) {
			ptrcpy(&(*H)->min, *x);
		}
	}
	(*H)->node_count += (*H)->node_count + 1;
}


Node *minimum(Heap *H) {
	return H->min;
}


void fib_heap_union(Heap **H, Heap **H1, Heap **H2) {
	make_fib_heap(H);

	(*H)->node_count = (*H1)->node_count + (*H2)->node_count;

	ptrcpy(&(*H)->min, (*H1)->min);
	
	if ((*H1)->min == NULL || ((*H2)->min != NULL && (*H2)->min->data < (*H1)->min->data)) {
		(*H)->min = (*H2)->min;
	}	

	if ((*H1)->min == NULL || (*H2)->min == NULL) 
		return;

	Node *H1_left = (*H1)->min->left;
	Node *H2_left = (*H2)->min->left;		

	
	ptrcpy(&(H1_left)->right, H2_left);
	ptrcpy(&(H2_left)->left, H1_left);
	
	ptrcpy(&(*H1)->min->left, (*H2)->min);
	ptrcpy(&(*H2)->min->right, (*H1)->min);

	
}

// void fib_heap_extract_min(Heap **H) {
// 	Node **z = &(*H)->min;
// 	if (*z != NULL) {
// 		Node *x = (*z)->child;
// 		while (x != NULL) {
// 			insert(H, x);
// 			ptrcpy(&x->parent, NULL);
// 			x = x->right;
// 		}
// 		if ((*z)->left == *z) {		// Heap has only one node
// 			(*H)->min = NULL;
// 			//free(z);
// 		}
// 		else {						// Atleast two nodes
// 			Node *left = (*z)->left;
// 			Node *right = (*z)->right;
// 			ptrcpy(&left->right, right);
// 			ptrcpy(&right->left, left);
// 			ptrcpy(&(*H)->min, (*z)->right);
// 			consolidate(H);
// 		}
// 		(*H)->node_count = (*H)->node_count - 1;
// 	}
// 	return z;
// }

// void consolidate(Heap **H) {

// }


int main() {
	int xmalloc_stat = xmalloc_init();
	
	if(xmalloc_stat == -1){
		// failed to launch Flask server
		return(0);
	}
	int n;
	scanf("%d", &n);
	Heap *H1;
	make_fib_heap(&H1);
	for(int i = 0; i < n; i++) {
		int data;
		scanf("%d", &data);
		Node *x;
		create_and_insert(&H1, &x, data);
	}
	xmalloc_bp("Created Heap#1");

	Heap *H2;
	scanf("%d", &n);
	make_fib_heap(&H2);
	for(int i = 0; i < n; i++) {
		int data;
		scanf("%d", &data);
		Node *x;
		create_and_insert(&H2, &x, data);
	}
	xmalloc_bp("Created Heap#2");

	Heap *H;
	fib_heap_union(&H, &H1, &H2);

}