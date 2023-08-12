#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include <string.h>

List *newList(){
    List *l;
    l = (List*) malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void print(List* l, int reverse) {
    if(l->head == NULL){
        printf("VAZIA\n");
        return;
    }
    Node *p;
    if(l->negative == -1)
        printf("-");

    if(reverse == 1){   
        p = l->tail;
        
        while(p != NULL){
            printf("%d", p->algarismo);
            p = p->prev;
        }
        printf("\n");
    }else{
        p = l->head;
        while(p->next != NULL) {
            printf("%d", p->algarismo);
            p = p->next;
        }
        printf("\n");
    }
}

void insert(List* l, int algarismo) {

    Node *new = (Node *)malloc(sizeof(Node)); 
    new->next = NULL;
    new->algarismo = algarismo;
    //new->prev = l->tail;

    //first node of the list
    if(l->head == NULL){
        new->prev = NULL;
        l->head = new;
    }
    
    else{
        new->prev = l->tail;
        l->tail->next = new;
    }

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

List* readNumber(){
    List* number = newList();
    char character = 'o';
    number->size = 0;
    number->negative = 1;
    while(character != ' ' && character != '\n' && character != '\r') {
        character = getchar();
        //tratamento de negativo
        if(character == '-')
            number->negative = -1; 
        else{ 
            //ignora os zeros no início do número     
            if((number->size == 0 && character != '0') || number->size != 0){
                insert(number, character - '0');
                number->size++;       
            }
        }
    };
    if(character == '\r')
        getchar();
    //dá as classes dos números de acordo com a posição
    Node* aux = number->tail->prev;
    int i = 0;
    while(aux != NULL){
        aux->classe = i++;
        aux = aux->prev;
    }
    number->size;
    //print(number, 0);
    return number;
}

List* addNumbers(List* num1, List* num2){
    List* result = newList();
    Node *aux1, *aux2, *resultAux;
    
    int maxDegree;

    if(num1->size > num2->size)
        maxDegree = num1->size;
    else 
        maxDegree = num2->size;

    result->size = maxDegree;
    aux1 = num1->tail->prev;
    aux2 = num2->tail->prev;
    resultAux = result->head;

    int carry = 0, sum;
    for(int i = 0; i < maxDegree-1; i++){
        sum = carry;
        int old1, old2;
        if(aux1 != NULL && i == aux1->classe){
            old1 = aux1->algarismo;
            sum += aux1->algarismo * num1->negative;
            aux1 = aux1->prev;
        }
        
        if(aux2 != NULL && i == aux2->classe){
            old2 = aux2->algarismo;
            sum += aux2->algarismo * num2->negative;
            aux2 = aux2->prev;
        }
        if(sum > 9){
            sum -= 10;
            carry = 1;
        }else if(sum > 19){
            sum -= 20;
            carry = 2;
        }else{
            carry = 0;
        }
        insert(result, abs(sum)); 
    }

    if(carry != 0)
        insert(result, abs(carry)); 

    return result;
}

int big(List *num1, List *num2){
    if(num1->negative == 1 && num2->negative == -1){
        return 1;
    }else if(num1->negative == -1 && num2->negative == 1){
        return 0;
    }else if(num1->negative == 1){
        if(num1->size > num2->size)
            return 1;
        else if(num1->size < num2->size)
            return 0;  
        else{
            Node *aux1, *aux2;
            aux1 = num1->head;
            aux2 = num2->head;
            while(aux1->next != NULL){
                if(aux1->algarismo > aux2->algarismo)
                    return 1;
                else{
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                }
                return 0;
            }            
        }
    }else{
        if(num1->size > num2->size)
            return 0;
        else if(num1->size < num2->size)
            return 1;
        else{
            Node *aux1, *aux2;
            aux1 = num1->head;
            aux2 = num2->head;
            while(aux1->next != NULL){
                if(aux1->algarismo < aux2->algarismo)
                    return 1;
                else{
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                }
                return 0;
            }
        }
    }
}

int eql(List *num1, List *num2){
    if(num1->size != num2->size)
        return 0;
    if(num1->negative != num2->negative)
        return 0;

    Node *aux1, *aux2;
    aux1 = num1->head;
    aux2 = num2->head;

    while(aux1->next != NULL){
        if(aux1->algarismo != aux2->algarismo)
            return 0;
        aux1 = aux1->next;
        aux2 = aux2->next;
    }
    return 1;
}
