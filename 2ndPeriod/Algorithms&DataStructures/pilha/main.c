#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"

int main(){
	pilha_t *p;
	int x;
	p = create();
	
	for(int i = 0; i < 10; i++){
		push(p, (elem)i);
	}

	while(!isEmpty(p)){
		pop(p, &x);
		printf("%d ", x);
	}

	return 0;
}
