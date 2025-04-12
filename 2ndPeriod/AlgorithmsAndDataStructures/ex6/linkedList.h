typedef struct NODE{
    int data;
    struct NODE* next;
} node;

void printList(node* head);
void insert(node** head, int data);
void girosflin(node** head, int rotations);