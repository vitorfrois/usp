typedef struct NODE{
    int algarismo, classe;
    struct NODE *next, *prev;
} Node;

typedef struct LIST{
    int size, negative;
    Node *head;
    Node *tail;
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
void print(List* l, int reverse);

/**
 * @brief Insert a new element in the tail of the linked list
 * 
 * @param l Linked List
 * @param newCoeff New coeficient
 */
void insert(List* l, int newCoeff);

/**
 * @brief Free the entire linked list
 * 
 * @param l Linked List
 */
void freeList(List* l);

/**
 * @brief Read and return a polynomial
 * 
 * @return the read polynomial
 */
List* readNumber();

/**
 * @brief add 2 positive numbers from the linked lists num1 and num2
 * 
 * @param num1 
 * @param num2 
 * @return List* the result
 */
List* addNumbers(List* num1, List* num2);

/**
 * @brief compare two numbers. If num 1 is bigger, return 1. Else, returns 0
 * 
 * @param num1 
 * @param num2 
 * @return int 
 */
int big(List *num1, List *num2);

/**
 * @brief check if the two entered numbers are equal.
 * 
 * @param num1 
 * @param num2 
 * @return int If they are, return 1. Else, 0;
 */
int eql(List *num1, List *num2);

