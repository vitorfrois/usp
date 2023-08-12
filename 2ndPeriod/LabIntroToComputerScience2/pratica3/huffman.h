#define ALPHABET_SIZE 128

typedef struct SYMBOL{
    char representation, *codified;
    int frequency;
}Symbol;

// typedef struct TNODE Node;
typedef struct NODE{
	Symbol s;
	struct NODE *left, *right;
}Node;

typedef struct NODEARRAY{
	Node **elements;
	int size;
}NodeArray;

void freeTree(Node *root);
int height(Node *root);
void printTree(Node *root, char *option);
void preOrder2(Node *root);
void preOrder(Node *root);
char *searchTree(Node *root, int freq, char *codified, int *x);
void huffmanDictionary(Node **root, char arr[], int top);
int isLeaf(Node *root);
NodeArray createPriorityQueue(int *charFrequency);
NodeArray createHuffmanTable(NodeArray array);
char *compress(Node **huffmanTable, char *message, int messageLenght);
void decompress(Node *root, char *compressed, int *i);
