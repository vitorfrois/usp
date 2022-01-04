#include <stdio.h>

int main() {
	int year;
	scanf("%d", &year);
	if(year % 400 == 0){
		printf("SIM\n");
		return 0;
	}
	if(year % 100 == 0){
		printf("NAO\n");
		return 0;
	}
	if(year % 4 == 0){
		printf("SIM\n");
		return 0;
	}
	printf("NAO\n");
	return 0;
}
