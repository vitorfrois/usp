#include <stdio.h>

int main(){
	//var define
	int samuWeight, loppaWeight;
	int years = 0;
	//input scaning
	scanf("%d %d", &samuWeight, &loppaWeight);
	//while loppa is heavier than samu, run this
	while (samuWeight <= loppaWeight){
		years++;
		samuWeight = samuWeight * 3 * years;
		loppaWeight = loppaWeight * 2 * years;	
		}
	printf("%d", years);
	return 0;

}
