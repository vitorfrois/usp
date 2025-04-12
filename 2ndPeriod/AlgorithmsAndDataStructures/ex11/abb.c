#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "abb.h"

struct node{
	Node *left, *right;
	int info;
};

/**
 * @brief Cria uma nova árvore binária de busca
 * 
 * @return BST* estrutura da árvore
 */
BST *create() {
	BST *a = (BST *)malloc(sizeof(BST));
	a->root = NULL;
	return a;
}

int isEmpty(BST *a) {
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

void printTree(Node *raiz, char *modo) {
	if(raiz == NULL) {
		printf("VAZIA");
	}else{
		if(strcmp(modo, "pre-ordem") == 0)
			preOrder(raiz);
		else if(strcmp(modo, "em-ordem") == 0)
			inOrder(raiz);
		else if(strcmp(modo, "pos-ordem") == 0)
			postOrder(raiz);
	}
	printf("\n");
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

void preOrder(Node *root) {
	if(root != NULL) {
		printf("%d ", root->info);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(Node *root) {
	if(root != NULL) {		
		inOrder(root->left);
		printf("%d ", root->info);
		inOrder(root->right);
	}
}

void postOrder(Node *root) {
	if(root != NULL) {		
		postOrder(root->left);		
		postOrder(root->right);
		printf("%d ", root->info);
	}
}

Node *search(Node *root, int x) {
	if(root == NULL) {
		return NULL;
	} else if(root->info == x) {
		return root;
	} else if(x < root->info) {
		return search(root->left, x);
	} else {
		return search(root->right, x);
	}
}

int insert(Node **root, int x) {
	if(*root == NULL) {
		*root = (Node *)malloc(sizeof(Node));
		(*root)->info = x;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return 1;
	} else if(x == (*root)->info) {
		return 0;
	} else if(x < (*root)->info) {
		return insert(&(*root)->left, x);
	} else {
		return insert(&(*root)->right, x);
	}
}

int bts_deletion(Node **root, int x) {
	if(*root == NULL) {
		return 0;
	} else if(x < (*root)->info) {
		return bts_deletion(&(*root)->left, x);
	} else if(x > (*root)->info) {
		return bts_deletion(&(*root)->right, x);
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
			return bts_deletion(&(*root)->left, aux->info);
		}
	}
}







