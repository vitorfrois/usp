#include <stdio.h>
#include <math.h>

int main(){
	float var, exp;
	scanf("%f %f", &var, &exp);
	float result = pow(var, exp);
	printf("%.4f", result);	
}	
