typedef struct PERSON{
    int id;
    char* name;
}Person;

typedef struct NODE{
    Person data;
    struct NODE *next, *prev;
} Node;

typedef struct LIST{
    Node *first, *last;
}List;

List *newList();
void print(List* l);
void insert(List* l, int id, char* name);
int removeItem(List *l, int id);
void freeList(List* l);
