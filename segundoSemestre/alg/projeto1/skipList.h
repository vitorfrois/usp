typedef struct ENTRY{
    char *word, *definition;
}Entry;

typedef struct NODE{
    int level;
    Entry data;
    struct NODE *next, *down;
} Node;

typedef struct SKIPLIST{
    int level;
    int lenght;
    int maxlevel;
    Node *upleft;
    Node **header;
}Skiplist;

Skiplist *newSkiplist();

Node* createNode(
	int level, 
	char *word, 
	char *definition,
	Node* next,
	Node* down
);

bool search(Skiplist *sl, char *word, bool verbose);
void insertEntry(Skiplist *sl, char *word, char *definition);
void updateEntry(Skiplist *sl, char *word, char *definition);
void removeEntry(Skiplist *sl, char *word);
void printSkiplist(Skiplist* sl, char* mode);
void freeList(Skiplist* sl);

