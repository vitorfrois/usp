#include <stdio.h>

int main(){
	int numValues, values;
	int min = 10e8;
	int max = 0;
	int feijoada = 0;
	scanf("%d\n", &numValues);
	for(int i = 0; i < numValues; i++){
		scanf("%d", &values);
		values < min? min = values: feijoada++;
		values > max? max = values: feijoada++;
	}
	printf("%d", max - min);
	return 0;

}	
