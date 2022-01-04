#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>

typedef long long int llint;

//Funções usadas na main

//Recebe a palavra, m e número de colisões e retorna o valor calculado pela função hash 
int hashing(char*, int, int);
//Funções para leitura de strings
int stringEnd(int, char[], char);
char* readString();

typedef struct elem{
    char *word;
    int number, hashCode;
}Elem;

int main(){
    //INSERÇÃO
    int n;
    scanf("%d\n", &n);
    int m = (n*13)/10;
    Elem* hashTable = malloc(sizeof(Elem) * m);

    //Preenche os elementos da tabela para permitir comparações
    for(int i = 0; i < m; i++){
        hashTable[i].word = "\0";
        hashTable[i].number = -1;
    }

    //Insere n elementos na tabela
    for(int i = 0; i < n; i++){
        Elem new;
        new.word = readString();
        scanf("%d\n", &new.number);
        int hashCode, colisions = 0;
        do{
            hashCode = hashing(new.word, m, colisions);
            colisions++;
        }while(hashTable[hashCode].number != -1);
        hashTable[hashCode] = new;
    }

    //Imprime os índices preenchidos da tabela
    for(int i = 0; i < m; i++)
        if(hashTable[i].number != -1)
            printf("%d %s-%d\n", i, hashTable[i].word, hashTable[i].number);
    

    printf("\n");
    //BUSCA
    int b;
    scanf("%d\n", &b);
    //Realiza b buscas na tabela
    for(int i = 0; i < b; i++){
        char *searchedWord = readString();
        printf("%s-", searchedWord);
        int hashCode, colisions = 0;
        do{
            hashCode = hashing(searchedWord, m, colisions);
            colisions++;
        }while(strcmp(hashTable[hashCode].word, searchedWord) != 0 && colisions < m);

        if(colisions != m)
            printf("%d\n", hashTable[hashCode].number);
        else
            printf("NE\n");

        free(searchedWord);
    }

    //Libera os espaços alocados
    for(int i = 0; i < m; i++)
        if(strcmp(hashTable[i].word,"\0") != 0) free(hashTable[i].word);

    free(hashTable);

    return 0;
}

//FUNÇÕES

int hashing(char *word, int m, int colisions){
    int size = (int) strlen(word);
    llint hashCode = 0; 
    for(int i = 0; i < size; i+=4)
        hashCode += (word[i] * (llint) pow(13.0, (double) (i/4)));

    hashCode = (hashCode + colisions) % m;
    return (int) hashCode;
}

int stringEnd(int numSeparators, char separatorArray[], char c){
    int end = 0;
    for(int i = 0; i < numSeparators; i++)
        if(c == separatorArray[i]) end = 1;

    return end;
}

char *readString(){
    //Armazena os separadores em um vetor de separadores
    char separatorArray[] = {'\n', EOF, '\r'};
    int numSeparators = (int) sizeof(separatorArray);

    //Declaração de variáveis
    int currentLenght = 0, step = 20;
    char c, *string = malloc(sizeof(char) * step);
    //Lê a palavra até encontrar um separador
    do{
        c = getchar();
        if (currentLenght >= step)
        {
            step *= 2;
            string = realloc(string, (step + 1) * sizeof(char *));
        }
        string[currentLenght] = c;
        currentLenght++;
    } while (stringEnd(numSeparators, separatorArray, c) != 1);
        
    //Últimos ajustes e retorna a string lida
    string[currentLenght-1] = '\0';
    string = realloc(string, (currentLenght-1) * sizeof(char *));
    
    if(c == '\r')
        getchar();
    
    return string;
}
