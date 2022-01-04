typedef struct NODE{
    char *word;
    struct NODE *next, *prev;
} Node;

typedef struct LIST{
    Node *head, *tail;
    Node **index;
    bool indexed;
}List;

List *newList();
void print(List* l);
void printHeader(List* l);
Node **indexIt(List *l);
void insert(List* l, char *name);
int removeItem(List *l, char *id);
int search(List *l, char *word);
void freeList(List* l);
