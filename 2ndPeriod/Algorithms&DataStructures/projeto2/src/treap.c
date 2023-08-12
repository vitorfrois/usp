#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../includes/treap.h"

Treap *create() {
	Treap *a = (Treap *)malloc(sizeof(Treap));
	a->root = NULL;
	return a;
}

int isEmpty(Treap *a) {
	assert(a != NULL);
	if(a->root == NULL)
		return 1;
	return 0;
}

void freeTree(Node *root) {
	if(root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

int height(Node *root) {
	if(root == NULL) 
		return 0;
	
	int alt_left = 1 + height(root->left);
	int alt_right = 1 + height(root->right);
	
	if(alt_left > alt_right)
		return alt_left;
	else
		return alt_right;
}

void printTree(Node *root, char *option) {
	if(strcmp(option, "preordem") == 0) preOrder(root);
	else if(strcmp(option, "ordem") == 0) inOrder(root);
	else if(strcmp(option, "posordem") == 0) postOrder(root);
	else if(strcmp(option, "largura") == 0) lenghtPrint(root); 
	else if(strcmp(option, "colored") == 0) preOrder2(root); 
	printf("\n");
}


void preOrder(Node *root) {
	if(root != NULL) {
		printf("(%d, %d) ", root->info, root->prio);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void preOrder2(Node *root) {
	if(root != NULL) {
		printf("\033[0;%dm", 31 + (root->info%8));
		printf("%d(", root->info);
		preOrder2(root->left);
		printf(",");
		preOrder2(root->right);
		printf("\033[0;%dm", 31 + (root->info%8));
		printf(")");
		printf("\033[0;39m");
	} else {
		printf("null");
	}
}

void inOrder(Node *root) {
	if(root != NULL) {		
		inOrder(root->left);
		printf("(%d, %d) ", root->info, root->prio);
		inOrder(root->right);
	}
}

void postOrder(Node *root) {
	if(root != NULL) {		
		postOrder(root->left);		
		postOrder(root->right);
		printf("(%d, %d) ", root->info, root->prio);
	}
}

void lenghtPrint(Node* root){
	Queue *q = createQueue(100);
	qPush(q, root);
	while(qIsEmpty(q) != 1)
		qPop(q);
}

Node **search(Node **root, int x) {
	if(*root == NULL) {
		return NULL;
	} else if((*root)->info == x) {
		return root;
	} else if(x < (*root)->info) {
		return search(&(*root)->left, x);
	} else {
		return search(&(*root)->right, x);
	}
}

int insert(Node **root, int info, int prio, Node ***updatesArray, int *h) {
	if(*root != NULL){
		updatesArray[*h] = root;
		*h += 1;
	}
	if(*root == NULL) {
		*root = (Node *)malloc(sizeof(Node));
		(*root)->info = info;
		(*root)->prio = prio;
		(*root)->left = NULL;
		(*root)->right = NULL;
		updatesArray[*h] = root;
		return 1;
	} else if(info == (*root)->info) {
		*h -= 1;
		printf("Elemento ja existente\n");
		return 0;
	} else if(info < (*root)->info) {
		return insert(&(*root)->left, info, prio, updatesArray, h);
	} else {
		return insert(&(*root)->right, info, prio, updatesArray, h);
	}
}

int deletion(Node **root, int x) {
	if(*root == NULL) {
		return 0;
	} else if(x < (*root)->info) {
		return deletion(&(*root)->left, x);
	} else if(x > (*root)->info) {
		return deletion(&(*root)->right, x);
	} else {
		if((*root)->left == NULL && (*root)->right == NULL) {
			free(*root);
			*root = NULL;
			return 1;
		}			
		else if((*root)->left == NULL) {
			Node *aux = *root;
			*root = (*root)->right;
			free(aux);
			return 1;
		}
		else if((*root)->right == NULL) {
			Node *aux = *root;
			*root = (*root)->left;
			free(aux);
			return 1;
		}		
		else {
			Node *aux = (*root)->left;
			while(aux->right != NULL) {
				aux = aux->right;
			}
			(*root)->info = aux->info;
			return deletion(&(*root)->left, aux->info);
		}
	}
}

void rightRotation(Node **p){
	Node *q = (*p)->left;
	Node *temp = q->right;
	q->right = *p;
	(*p)->left = temp;
	*p = q;
}

void leftRotation(Node **p){
	Node *q = (*p)->right;
	Node *temp = q->left;
	q->left = *p;
	(*p)->right = temp;
	*p = q;
}

void treapInsertion(Treap *t, int info, int prio){
	// Node ***: array of pointers to Node *	
	Node ***updatesArray = malloc(sizeof(Node*) * (height(t->root) + 1));
	int h = 0;
	insert(&t->root, info, prio, updatesArray, &h);

	int verbose = 0;

	while(h > 0 && (*updatesArray[h-1])->prio < (*updatesArray[h])->prio){
		if((*updatesArray[h-1])->right != NULL && (*updatesArray[h-1])->right->prio == (*updatesArray[h])->prio){
			if(verbose) printf("Antes de rotacionar a esquerda: ");
			if(verbose) printf("updates[%d] é %d\n", h-1, (*updatesArray[h-1])->info);
			leftRotation(updatesArray[h-1]);
			if(verbose) printf("updates[%d] é %d\n", h-1, (*updatesArray[h-1])->left->info);

		}
		else{
			if(verbose) printf("Antes de rotacionar a direita: ");
			if(verbose) printf("root->left = %d\n", t->root->left->info);
			if(verbose) printf("updates[%d] é %d\n", h-1, (*updatesArray[h-1])->info);
			rightRotation(updatesArray[h-1]);
			if(verbose) printf("root->left = %d\n", t->root->left->info);
		}
		h--;
	}
	free(updatesArray);
}
 


