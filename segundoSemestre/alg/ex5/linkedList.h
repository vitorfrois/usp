typedef struct NODE{
    char data;
    struct NODE* next;
} node;

void printList(node* head);
int isEmpty(node* head);
void insert(node** head, char data);
