typedef struct PROCESSO{
    int p0, t0, tf, r;
}Processo;

typedef struct NODE{
    Processo data;
    bool on;
    struct NODE *next, *prev;
}Node;

typedef struct LIST{
    Node *head, *tail;
    int size, total_i, t;
}List;

/**
 * @brief create a new linked list
 * 
 * @return List* 
 */
List* newList();

/**
 * @brief Remove a given node from the Linked List l and print current running time
 * 
 * @param l linkedList
 * @param rem Node to be removed
 * @return int 1 if the deletion was successful
 */
int removeNode(List *l, Node *rem);

Node* createNode(int p0, int t0, int tf, int r);

/**
 * @brief Search for a node with code p0
 * 
 * @param l linkedList
 * @param p0 
 * @return true if the code is in l
 * @return false 
 */
bool search(List *l, int p0); 

/**
 * @brief Insert a node with listed parameters in l
 * 
 * @param l linkedList 
 * @param p0 process code
 * @param t0 starting time
 * @param tf total time
 * @param r priority
 * @param mode 'r' to sort by priority (descending) and 't' to sort by starting time
 */
void insert(List *l, int p0, int t0, int tf, int r, char);

/**
 * @brief print the parameters of a given Node
 * 
 * @param n Node
 */
void printNode(Node *aux);

/**
 * @brief print the linkedList cyclically starting from Node l
 * 
 * @param l linkedList
 * @param aux Initial Node
 */
void printList(List *l, Node* aux);

/**
 * @brief run 'Simulador de Escalonamento de Processos', based on a waitList of process
 * 
 * @param waitList where each process has p0, t0, tf & r
 * @param verbose if true, print debug help
 */
void run(List *l, bool verbose);

/**
 * @brief Frees list 
 * 
 * @param l 
 */
void freeList(List *l);
