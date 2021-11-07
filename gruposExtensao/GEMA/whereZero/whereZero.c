#include <stdio.h>

int main() {
	int l, c, mtxNumber;//l stands for lines and c for columns
	int lPosition, cPosition;
	scanf("%d %d", &l, &c);
	int matrix[l][c];
	for(int a = 0; a < l; a++){
		for(int b = 0; b < c; b++){
			scanf("%d", &mtxNumber);
			if(mtxNumber == 0){
				lPosition = a;
				cPosition = b;
				}
			}
		}
	printf("%d %d", lPosition, cPosition);
}

