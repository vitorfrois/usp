typedef struct node Node;

typedef struct arvore {
	Node *root;
}BST;

BST *create();
int isEmpty(BST *a);
void freeTree(Node *root);
void printTree(Node *root);
int height(Node *root);
void preOrder(Node *root);
void inOrder(Node *root);
void postOrder(Node *root);
Node *search(Node *root, int x);
int insert(Node **root, int x);
int BSTdeletion(Node **root, int x);
