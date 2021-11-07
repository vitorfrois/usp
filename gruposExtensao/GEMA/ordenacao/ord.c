#include <stdio.h>

int main(){
	int a, b, c, maior, meio, menor;	
	scanf("%d\n%d\n%d", &a, &b, &c);
	if(a > b && b > c){maior = a; meio = b; menor = c;}
	if(a > c && c > b){maior = a; meio = c; menor = b;}
	if(b > a && a > c){maior = b; meio = a; menor = c;}
	if(b > c && c > a){maior = b; meio = c; menor = a;}
	if(c > a && a > b){maior = c; meio = a; menor = b;}
	if(c > b && b > a){maior = c; meio = b; menor = a;}
	
	
	printf("%d\n%d\n%d", maior, meio, menor);
	return 0;
}
