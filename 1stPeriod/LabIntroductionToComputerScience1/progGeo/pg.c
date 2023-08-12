#include <stdio.h>
#include <math.h>

int main(){
	float a1, q, n;
	float an, sn;
	scanf("%f %f %f", &a1, &q, &n);
	an = a1 * pow((double)q, (double)(n-1));
	sn = a1 * (pow((double)q, (double)n) - 1)/(q-1);
	printf("%.2f\n%.2f", an, sn);
}
