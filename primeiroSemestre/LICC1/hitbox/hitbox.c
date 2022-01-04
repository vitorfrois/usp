#include <stdio.h>
#include <stdbool.h> 

int sort(long long int number[]);

long long int xAxisCalculus (long int x1, long int x2, long int width1, 
	long int width2, long long int result[]);
long long int yAxisCalculus (long int y1, long int y2, long int height1, 
	long int height2, long long int result[]);

int main(){
	bool miss = false; //0 hit 1 miss
	long int x1, x2, width1, width2;
	long int y1, y2, height1, height2;
	long long int result[5]; //x, y, Width, height
	scanf("%ld %ld %ld %ld", &x1, &y1, &width1, &height1);
	scanf("%ld %ld %ld %ld", &x2, &y2, &width2, &height2);
	xAxisCalculus(x1, x2, width1, width2, result);
	yAxisCalculus(y1, y2, height1, height2, result);
	
	//check x axis values
	if(x1 > x2){
		if(x2 + width2 < x1){
		miss = true;
		}	
	}else{
		if(x1 + width1 < x2){
		miss = true;
		}
	}
	
	//checking y axis
	if(y1 > y2){
		if(y2 + height2 < y1){
		miss = true;
		}
	}else{
		if(y1 + height1 < y2){
		miss = true;
		}
	}
	
	//print miss and hit cases
	if(miss == true){
		printf("MISS\n");
		return 0;
	}else{
		printf("HIT: ");
		for(int i = 0; i < 4; i++)
			printf("%lld ", result[i]);
	}
	printf("\n");
	return 0;
}

long long int xAxisCalculus (long int x1, long int x2, long int width1, long int width2, long long int result[]){
	width1 = width1 + x1;
	width2 = width2 + x2;
	long long int matrixX[] = {x1, x2, width1, width2};
	sort(matrixX);
	result[2] = matrixX[2] - matrixX[1]; //but if finalWidth > width1
	result[0] = matrixX[1];
	return *result;
}

long long int yAxisCalculus (long int y1, long int y2, long int height1, long int height2, long long int result[]){
	height1 = height1 + y1;
	height2 = height2 + y2;
	long long int matrixY[] = {y1, y2, height1, height2};
	sort(matrixY);
	result[3] = matrixY[2] - matrixY[1]; //but if finalheight > height1
	result[1] = matrixY[1];
	return *result;
}

int sort(long long int number[]){
	int i, j, a, n = 4; //matriz de 4 valores
	for (i = 0; i < n; ++i){
          for (j = i + 1; j < n; ++j){
               if (number[i] > number[j]){
                   a =  number[i];
                   number[i] = number[j];
                   number[j] = a;
               }
          }
      }
	return *number;
}
