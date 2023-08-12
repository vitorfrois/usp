#include <stdio.h>
#include <stdbool.h>

int main(){
	int x, y, z;
	bool vdd = false;
	printf("Insert x and y: ");
	scanf("%i", &x);
	scanf("%i", &y);
	if (x < y){
		printf(" x < y == true");
	}
	else{
		printf(" x < y == false");
	}
	printf("\n Insert z: ");
	scanf("%i", &z);
	if (z*x < z*y){
		printf(" xz < yz == true");
	}
	else{
		printf(" xz < yz == false");
	}
	return 0;
}