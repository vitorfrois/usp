#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// #include "huffman.h"
#include "sorts.h"

/**
 * @brief Frees the tree recursively
 * 
 * @param root the root node of the tree
 */
void freeTree(Node *root) {
	if(root != NULL) {
		if(root->s.representation != '$') free(root->s.codified);
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

/**
 * @brief Computes the heigth of the tree
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
 * @brief Prints the tree recursively
 * 
 * @param root the primary root
 */
void printTree(Node *root, char *option) {
	if(strcmp(option, "preordem") == 0) preOrder(root);
	else if(strcmp(option, "colored") == 0) preOrder2(root); 
	printf("\n");
}

void preOrder2(Node *root) {
	if(root != NULL) {
		printf("\033[0;%dm", 31 + (root->s.frequency%8));
		printf("%c;%d(", root->s.representation, root->s.frequency);
		preOrder2(root->left);
		printf(",");
		preOrder2(root->right);
		printf("\033[0;%dm", 31 + (root->s.frequency%8));
		printf(")");
		printf("\033[0;39m");
	} else {
		printf("null");
	}
}

/**
 * @brief The root node gets visited first, followed by left and right subtrees. 
 * 
 * @param root the primary root
 */
void preOrder(Node *root) {
	if(root != NULL) {
		printf("%d ", root->s.frequency);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/**
 * @brief Search the root with info x
 * 
 * @param root the primary root
 * @param x the key
 * @return Node* 
 */
char *searchTree(Node *root, int freq, char *codified, int *x) {
	if(root) printf("nó atual = %d; procurando por %d\n", root->s.frequency, freq);
	if(freq > root->s.frequency) {
		codified[*x] = '1';
		*x += 1;
		searchTree(root->right, freq, codified, x);
	}else if(freq < root->s.frequency) {
		codified[*x] = '0';
		*x += 1;
		searchTree(root->left, freq, codified, x);
	}else if(freq == root->s.frequency){
		return codified;
	}
	return "uai";
}

void huffmanDictionary(Node** root, char arr[], int top){
	// if(*root) printf("nó atual = %c; top = %d\n", (*root)->s.representation, top);
    // Assign 0 to left edge and recur
    if ((*root)->left) {
        arr[top] = '0';
        huffmanDictionary(&(*root)->left, arr, top + 1);
    }
    // Assign 1 to right edge and recur
    if ((*root)->right) {
        arr[top] = '1';
        huffmanDictionary(&(*root)->right, arr, top + 1);
    }
    if (isLeaf((*root))) {
		(*root)->s.codified = malloc(sizeof(char) * (top + 1));
		for(int i = 0; i < top; i++)
			(*root)->s.codified[i] = arr[i];
		(*root)->s.codified[top] = '\0';
        // printf("%c: ", (*root)->s.representation);
		// for(int i = 0; i < top; i++)
		// 	printf("%c", arr[i]);
		// printf("\n");
    }
}

int isLeaf(Node* root){
    return !(root->left) && !(root->right);
}

NodeArray createPriorityQueue(int *charFrequency){
	NodeArray array;
	array.size = 0;
	array.elements = malloc(sizeof(Node*) * ALPHABET_SIZE);
	for (int i = 0; i < ALPHABET_SIZE; i++){
        if(charFrequency[i] != 0){
            array.elements[array.size] = malloc(sizeof(Node));
            array.elements[array.size]->left = NULL;
            array.elements[array.size]->right = NULL;
            array.elements[array.size]->s.representation = (char) i;
            array.elements[array.size]->s.frequency = charFrequency[i];
            array.size += 1;
        }
    }
    quicksort(array.elements, 0, array.size);
	return array;
}

NodeArray createHuffmanTable(NodeArray array){
	NodeArray huffmanTable;
	huffmanTable.size = array.size;
	huffmanTable.elements = malloc(sizeof(Node*) * ALPHABET_SIZE);
    for(int i = 0; i < huffmanTable.size; i++)
        huffmanTable.elements[i] = array.elements[i];

	while(array.size > 1){
        Node *left = array.elements[--array.size];
        Node *right = array.elements[--array.size];
        Node *newNode = malloc(sizeof(Node));
        newNode->left = left;
        newNode->right = right;
        newNode->s.frequency = left->s.frequency + right->s.frequency;
        newNode->s.representation = '$';
        array.elements[array.size++] = newNode;
        // printTree(newNode, "colored");
        quicksort(array.elements, 0, array.size);
    }
	//create huffman table
    int top = 0;
    char arr[height(array.elements[0])];
    huffmanDictionary(&array.elements[0], arr, top);

	return huffmanTable;
}

char *compress(Node **huffmanTable, char *message, int messageLenght){
    int compressedSize = 0, oldCompressedSize;
	char *compressed = malloc(sizeof(char));
    for(int i = 0, hi; i < messageLenght; i++){
        hi = 0;
        while(huffmanTable[hi]->s.representation != message[i])
            hi++;
        // printf("%s", huffmanTable[hi]->s.);
        // printf("%c = %s; ", huffmanTable[hi]->s.representation, huffmanTable[hi]->s.codified);
        oldCompressedSize = compressedSize;
        compressedSize += strlen(huffmanTable[hi]->s.codified);
        // printf("csize = %d; old = %d\n", compressedSize, oldCompressedSize);
        compressed = realloc(compressed, sizeof(char) * (compressedSize + 1));
        strcat(compressed, huffmanTable[hi]->s.codified);
    }
	return compressed;
}

void decompress(Node *root, char *compressed, int *i){
	// printf("compressed[%d]=%c\n", *i, compressed[*i]);
	// printf("nó atual=%c: ", root->s.representation);
	if(isLeaf(root)){
		*i -= 1;
		printf("%c", root->s.representation);
		return;
	}
	if(compressed[*i] == '0'){
		*i += 1;
		// printf("esq!\n");	
		decompress(root->left, compressed, i);
	}
	else if(compressed[*i] == '1'){
		*i += 1;
		// printf("dir!\n");	
		decompress(root->right, compressed, i);
	}
}



