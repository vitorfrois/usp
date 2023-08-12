typedef struct NODE{
    char *word;
    struct NODE *next, *prev;
} Node;

typedef struct LIST{
    int size;
    Node *head;
}List;

/**
 * @brief creates a new Linked List
 * 
 * @return Linked List
 */
List *newList();

/**
 * @brief Prints a linked list
 * 
 * @param l Linked List to be printed
 */
void print(List* l);

/**
 * @brief Insert a new element in the tail of the linked list
 * 
 * @param l Linked List
 * @param newCoeff New coeficient
 */
void insert(List* l, char *word);

/**
 * @brief Remove node with param word from Linked List
 * 
 * @param l 
 * @param word 
 * @return int 1 if deletion was succesful
 */
int removeNode(List *l, char *word);

/**
 * @brief Search for word in Linked List l
 * 
 * @param l 
 * @param word 
 * @return true if word was found
 * @return false else
 */
bool search(List *l, char *word);

/**
 * @brief Free the entire linked list
 * 
 * @param l Linked List
 */
void freeList(List* l);
