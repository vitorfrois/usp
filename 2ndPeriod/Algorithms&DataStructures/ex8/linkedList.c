#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include <string.h>

List *newList(){
    List *l;
    l = (List*) malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    l->degree = 0;
    return l;
}

void print(List* l) {
    if(l->head == NULL){
        printf("VAZIA\n");
        return;
    }

    Node *p = l->head;

    if(p->next == NULL){
        printf("(%d)\n", p->coefficient);
        return;
    }
    printf("(");

    while(p->next != NULL) {
        printf("%d,", p->coefficient);
        p = p->next;
    }
    printf("%d)\n", p->coefficient);
}

void insert(List* l, int newCoeff) {

    Node *new = (Node *)malloc(sizeof(Node)); 
    new->next = NULL;
    new->coefficient = newCoeff;

    //first node of the list
    if(l->head == NULL)
        l->head = new;
    else
        l->tail->next = new;

    l->tail = new;
    
}

void freeList(List *l) {
	if(l != NULL) {
		Node *aux = l->head;
		while(aux != NULL) {
			l->head = aux->next;
			free(aux);
			aux = l->head;
		}
		free(l);
	}else{
        printf("uai\n");
    }
}

List* readPolynomial(){
    List* polynomial = newList();
    char* string = malloc(sizeof(char));
    char character = 'o';
    int nCharsString = 0, nNumbers = 0;
    polynomial->degree = 0;
    do {
        character = getchar();
        if(character == ')' || character == ','){
            string[nCharsString] = '\0';
            insert(polynomial, atoi(string));
            memset(string, 0, strlen(string));
            nNumbers++;
            nCharsString = 0;
            polynomial->degree++;
        }else if(character == ' ' || character == '(' || character == '\n'){
            //do nothing
        }else{
            string = realloc(string, (nCharsString + 1) * sizeof(char*));
            string[nCharsString] = character;
            nCharsString++;
        }
    } while(character != ')');
    free(string);
    getchar();
    getchar();
    return polynomial;
}

List* addPolynomials(List** polynomials, int nPolynomials){
    List* result = newList();
    Node* aux;
    
    int maxDegree = 0;

    //find the bigger polynomial degree
    for(int i = 0; i < nPolynomials; i++)
        if(polynomials[i]->degree > maxDegree)
            maxDegree = polynomials[i]->degree;
    
    result->degree = maxDegree;

    //itera pelos graus de todos os polinomios, somando-os
    //iterate over all degrees, adding them up
    for(int i = 0; i < maxDegree; i++){
        int sum = 0;
        for(int j = 0; j < nPolynomials; j++){
            aux = polynomials[j]->head;
            int n = 0;
            while(n < i && aux != NULL){
                aux = aux->next;
                n++;
            }
            if(aux != NULL){
                sum += aux->coefficient;
            }
        }
        insert(result, sum);
    }
    return result;
}
