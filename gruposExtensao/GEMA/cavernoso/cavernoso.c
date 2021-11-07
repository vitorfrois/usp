#include <stdio.h>

int main(){
	int inputSize, count, maior;
	char input;
	scanf("%c", &input);
	printf("%c", input);
	for(int i; i < input; i++){
		
		while(input != 0){
			input = input/10;
			count++;
		}
	}
	printf("%d", input);
}
