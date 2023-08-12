#include <stdio.h>
#include <stdlib.h>

int main() {
	char symbol;
	int triangleHeight;
	scanf("%d %c", &triangleHeight, &symbol);
	if(triangleHeight < 1 || triangleHeight > 25){
		printf("Altura invalida");
		exit(0);
	}
	for(int i = 1; i < triangleHeight + 1; i++){
		for(int n = 0; n < (triangleHeight - i); n++){
			printf(" ");
		}
		for(int n = 0; n < (2 * i - 1); n++){
			printf("%c", symbol);
		}
		for(int n = 0; n < (triangleHeight - i); n++){
			printf(" ");
		}
		printf("\n");	
	}
	return 0;
}	
