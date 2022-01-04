#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "linkedList.h"
#include "myString.h"

typedef long long int llint;
#define HASH_P 1000000007
#define HASH_X 263

//Funções usadas na main

void add(List **, int);
void del(List **, int);
void get(List **);
void check(List **, int);

int main(){
    char *input = "s";
    int m;
    scanf("%d\n", &m);
    List **hashTable = malloc(sizeof(List*) * m);
    for(int i = 0; i < m; i++)
        hashTable[i] = newList();
    
    int iterations;
    scanf("%d\n", &iterations);
    for(int j = 0; j < iterations; j++){
        input = readString();
        if(strcmp(input, "add") == 0) add(hashTable, m); 
        else if(strcmp(input, "del") == 0) del(hashTable, m);
        else if(strcmp(input, "get") == 0) get(hashTable);   
        else if(strcmp(input, "check") == 0) check(hashTable, m);
        else printf("opção não encontrada\n");
        free(input);
    }
    for(int i = 0; i < m; i++)
        freeList(hashTable[i]);
    free(hashTable);

    return 0;
}

int hashing(char *word, int m){
    int size = (int) strlen(word);
    llint hashCode = 0, p = HASH_P, x = HASH_X; 
    for(int i = 0; i < size; i++)
        hashCode = hashCode + ((word[i] * (llint) pow(x, (double) i)) % p);
    
    hashCode = (hashCode % p) % m;
    return (int) hashCode;
}

void add(List **hashTable, int m){
    char *word = readString();
    int hashCode = hashing(word, m);
    insert(hashTable[hashCode], word);
}

void del(List **hashTable, int m){
    char *word = readString();
    int hashCode = hashing(word, m);
    removeNode(hashTable[hashCode], word);
}
 
void get(List **hashTable){
    int index;
    scanf("%d\n", &index);
    print(hashTable[index]);
}
void check(List **hashTable, int m){
    char *word = readString();
    int hashCode = hashing(word, m);
    if(search(hashTable[hashCode], word)) printf("sim\n");
    else printf("não\n");
}

