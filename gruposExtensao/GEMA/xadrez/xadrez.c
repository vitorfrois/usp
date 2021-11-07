#include <stdio.h>

int main(){
	int a, b, c;
	scanf("%d %d", &a, &b);
	c = a*b;
	if(c%2 != 0){
		c = c/2 + 1;
		printf("%d", c);
	}else{
		c = c/2;
		printf("%d", c);
	}
}



