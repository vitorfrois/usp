typedef struct NODE{
    int coefficient;
    struct NODE *next;
} Node;

typedef struct LIST{
    int degree;
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
void print(List* l);

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
List* readPolynomial();

/**
 * @brief Sum all polynomials in array polynomials
 * 
 * @param polynomials Array of polynomials
 * @param nPolynomials Number of polynomials
 * @return the result of summed polynomials
 */
List* addPolynomials(List** polynomials, int nPolynomials);
