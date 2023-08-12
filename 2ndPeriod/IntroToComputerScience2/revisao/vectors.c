#include <stdio.h>
#include <stdlib.h>

int main(){
	int numbers[1001] = {0}, negative_numbers[1001] = {0}, n = 0;
	char character;
	int array[100];
	while((character = getchar()) != EOF){ 
		ungetc(character, stdin);
		scanf("%d ", &array[n]);
		if(array[n] > -1){
			numbers[array[n]]++;
		}else{
			negative_numbers[abs(array[n])]++;
		}
		n++;
	}
	
	for(int i = 0; i < n; i++){
		//printf("array(%d) = %d\n", i, array[i]);
		if(numbers[array[i]] > 0 && array[i] > -1){
			printf("%d (%d)\n", array[i], numbers[array[i]]);
			numbers[array[i]] = 0;
		}
		if(negative_numbers[abs(array[i])] > 0 && array[i] < 0){
			printf("%d (%d)\n", array[i], negative_numbers[abs(array[i])]);
			negative_numbers[abs(array[i])] = 0;

		}
	}

	
	return 0;
}
