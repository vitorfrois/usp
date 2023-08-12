#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abb.h"

int main(void) {
	BST *a = create();
	
	insert(&a->root, 5);
	insert(&a->root, 3);
	insert(&a->root, 7);
	insert(&a->root, 9);
	insert(&a->root, 8);
	insert(&a->root, 2);
	
	printTree(a->root);
	printf("\n");

	BSTdeletion(&a->root, 5);
	printTree(a->root);
	printf("\n");

	
	return 0;
}