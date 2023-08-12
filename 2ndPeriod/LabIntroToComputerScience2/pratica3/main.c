#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include "myString.h"

int main()
{
    int charFrequency[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++)
        charFrequency[i] = 0;

    char *message = readString();
    int messageLenght = strlen(message); 
    for(int i = 0; i < messageLenght; i++)
        charFrequency[(int) message[i]]++;

    NodeArray prioQueue, huffmanTable;
    prioQueue = createPriorityQueue(charFrequency);
    Node **root = &prioQueue.elements[0];
    huffmanTable.size = prioQueue.size;
    huffmanTable = createHuffmanTable(prioQueue);

    char *compressed = compress(huffmanTable.elements, message, messageLenght);
    int compressedSize = strlen(compressed);
    for(int i = 0; i < compressedSize; i++)
        decompress(*root, compressed, &i);
    
    double Scp = (double) compressedSize, S0 = (double) messageLenght;
    printf("\nIndice de compressao: %.2lf\n", (Scp)/(8*S0));    

    //frees
    free(compressed);
    free(message);
    freeTree(*root);
    free(prioQueue.elements);
    free(huffmanTable.elements);
    // for(int i = 0; i < queueSize; i++)
    //     free(prioQueue[queueSize]);
    // free(nodeArray);

    return 0;
}
