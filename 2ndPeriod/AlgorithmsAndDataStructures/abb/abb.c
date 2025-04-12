#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abb.h"

struct node {
	Node *left, *right;
	int info;
};

/**
 * @brief Create a new Binary Search Tree (BTS)
 * 
 * @return BST* 
 */
BST *create() {
	BST *a = (BST *)malloc(sizeof(BST));
	a->root = NULL;
	return a;
}

/**
 * @brief Check if the tree is empty
 * 
 * @param a tree
 * @return int 1 for empty, else, 0
 */
int isEmpty(BST *a) {
	assert(a != NULL);
	if(a->root == NULL)
		return 1;
	return 0;
}

/**
 * @brief Frees the BST recursively
 * 
 * @param root the root node of the tree
 */
void freeTree(Node *root) {
	if(root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

/**
 * @brief Prints the tree recursively
 * 
 * @param root the primary root
 */
void printTree(Node *root) {
	if(root != NULL) {
		printf("%d(", root->info);
		printTree(root->left);
		printf(",");
		printTree(root->right);
		printf(")");
	} else {
		printf("null");
	}
}

/**
 * @brief Computes the heigth of the bst
 * 
 * @param root the primary root
 * @return the height (int)
 */
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

/**
 * @brief The root node gets visited first, followed by left and right subtrees. 
 * 
 * @param root the primary root
 */
void preOrder(Node *root) {
	if(root != NULL) {
		printf("%d ", root->info);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/**
 * @brief  Nodes from the left subtree get visited first, followed by the root node and right subtree.
 * 
 * @param root the primary root 
 */
void inOrder(Node *root) {
	if(root != NULL) {		
		inOrder(root->left);
		printf("%d ", root->info);
		inOrder(root->right);
	}
}

/**
 * @brief Nodes from the left subtree get visited first, followed by the right subtree, and finally the root.
 * 
 * @param root the primary root
 */
void postOrder(Node *root) {
	if(root != NULL) {		
		postOrder(root->left);		
		postOrder(root->right);
		printf("%d ", root->info);
	}
}

/**
 * @brief Search the root with info x
 * 
 * @param root the primary root
 * @param x the key
 * @return Node* 
 */
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

/**
 * @brief Insert a new element with value x in the tree 
 * 
 * @param root the primary root
 * @param x value to be inserted
 * @return int 1 if the insertion was sucessful
 */
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

/**
 * @brief Deletes a root with value x
 * 
 * @param root the primary root
 * @param x value to be deleted from the bst
 * @return int 1 if the deletion was sucessful
 */
int BSTdeletion(Node **root, int x) {
	if(*root == NULL) {
		return 0;
	} else if(x < (*root)->info) {
		return BSTdeletion(&(*root)->left, x);
	} else if(x > (*root)->info) {
		return BSTdeletion(&(*root)->right, x);
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
			return BSTdeletion(&(*root)->left, aux->info);
		}
	}
}







