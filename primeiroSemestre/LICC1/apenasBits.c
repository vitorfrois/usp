#include <stdio.h>

int main(){
	int input;
	scanf("%d", &input);
	for(int i = 3; i > -1; i--){
		int shifted = input >> (8*i);
		char andMask = shifted & 255;
		printf("%c", andMask);
	}
	return 0;	
}
