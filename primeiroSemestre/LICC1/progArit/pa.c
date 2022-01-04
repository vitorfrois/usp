#include <stdio.h>

int main(){
	long int a1, r, n;
	long int an, sn;
	scanf("%ld %ld %ld", &a1, &r, &n);
	an = a1+(n-1)*r;
	sn = (a1+an)*n/2;
	printf("%ld\n%ld", an, sn);
}
