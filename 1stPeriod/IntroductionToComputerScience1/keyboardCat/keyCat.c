#include <stdio.h>

int main() {
	int number;
	char arrayChar[49] = {'0'};
	for(int i = 0; i < 49; i++){
		scanf("%c ", &arrayChar[i]);
	}
	
	int textLenght;	
	scanf("%d", &textLenght);
	for(int l = 0; l < textLenght; l++){
		scanf("%d ", &number);
		switch (arrayChar[number]) {
			case 'E':
				printf("\n");
				break;
			case '_':
				printf(" ");
				break;
			default:
				printf("%c", arrayChar[number]);
			}
		}
}
