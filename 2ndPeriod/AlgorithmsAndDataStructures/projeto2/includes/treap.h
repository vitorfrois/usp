#ifndef TREAP_H
#define TREAP_H

#include "queue.h"

typedef struct arvore {
	Node *root;
}Treap;

/**
 * @brief create a new Heap Tree (Treap) struct.
 * 
 * @return Treap* 
 */
Treap *create();

/**
 * @brief check if treap is empty
 * 
 * @param a 
 * @return int 1 if empty; else, else 0;
 */
int isEmpty(Treap *a);

/**
 * @brief Free treap from root Node.
 * 
 * @param root 
 */
void freeTree(Node *root);

/**
 * @brief Computate treap height
 * 
 * @param root 
 * @return int treap height
 */
int height(Node *root);

/**
 * @brief print treap according to options
 * 
 * @param root 
 * @param option "preordem", "ordem", "posordem", "largura", "colored".
 */
void printTree(Node *root, char *option);

//All possible printing functions

/**
 * @brief The root node gets visited first, followed by left and right subtrees. 
 * 
 * @param root the primary root
 */
void preOrder(Node *root);

/**
 * @brief Preorder insertion but colored. 
 * 
 * @param root the primary root
 */
void preOrder2(Node *root);

/**
 * @brief  Nodes from the left subtree get visited first, followed by the root node and right subtree.
 * 
 * @param root the primary root 
 */
void inOrder(Node *root);

/**
 * @brief Nodes from the left subtree get visited first, followed by the right subtree, and finally the root.
 * 
 * @param root the primary root
 */
void postOrder(Node *root);

/**
 * @brief Preorder printing with level priority (nodes closer to the root get printed first)
 * 
 * @param root 
 */
void lenghtPrint(Node *root);

/**
 * @brief search for a node with info == x.
 * 
 * @param root Treap root
 * @param x 
 * @return Node** Adress of searched node; NULL if it was not found.
 */
Node **search(Node **root, int x);

/**
 * @brief Insert a node Treap
 * 
 * @param root Treap root
 * @param info 
 * @param prio 
 * @param updatesArray Array that stores travelled nodes
 * @param h current height
 * @return int 1 if the insertion was succesful, else returns 0.
 */
int insert(Node **root, int info, int prio, Node ***updatesArray, int *h);

/**
 * @brief Delete a node with info == x.
 * 
 * @param root 
 * @param x 
 * @return int 1 if the deletion was succesful, else returns 0.
 */
int deletion(Node **root, int x);

/**
 * @brief Rotates node p to the right
 * @param p 
 */
void rightRotation(Node **p);

/**
 * @brief Rotates node p to the left
 * 
 * @param p 
 */
void leftRotation(Node **p);

/**
 * @brief Inserts nodes with info and priority in Treap t
 * 
 * @param t 
 * @param info 
 * @param prio 
 */
void treapInsertion(Treap *t, int info, int prio);

#endif 

