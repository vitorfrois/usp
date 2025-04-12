
typedef struct {
    int n;
    char* word;
}wordList;

void dataCpy(wordList* a, wordList* b);
int dataCmp(wordList* a, wordList* b);
wordList* insertionSort(wordList* data, int totalWords);