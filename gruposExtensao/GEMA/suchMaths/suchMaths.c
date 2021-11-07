#include <stdio.h>

int main(){
	int x, y, p;
	scanf("%d", &p);
	if(p==2){
		printf("0"); //não existe solução para p = 2
		return 0;
	}		
	x = (p+1)/2;
	y = x - 1;
	printf("1\n%d %d", x, y);
	return 0;
}
