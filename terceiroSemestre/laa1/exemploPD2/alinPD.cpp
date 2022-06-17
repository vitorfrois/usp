#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX 100

#define MIN(a,b,c)  min(min((a), (b)), (c))  

char str1[MAX] = "ocurrance";
char str2[MAX] = "occurrence";

int tstr1 = strlen(str1);
int tstr2 = strlen(str2);


int M[100][100];

int delta = 2;


//int minimo(int x, int y, int z){
//    return min(min(x, y), z);
//}

void printM(){
	for (int j = tstr2; j >= 0 ; j--){
		for (int i = 0; i <= tstr1; i++)
			printf("\t%d ", M[i][j]);
		printf("\n");
	}
	printf("\n");
}

int alpha(int i, int j){
	int res;
	char c1 = str1[i];
	char c2 = str2[j];
	if (c1 == c2)
	  res = 0;
    else 
	if ( (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')  && 
		 (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u') )
		res =  1;
	else if ( !(c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')  && 
		 !(c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u') )
			res = 1;
		 else res = 3;

	printf("%c ** %c === res = %d\n", c1, c2, res);
	return res;
}

int alin(int m, int n){
	for (int i = 0; i <=m; ++i)
		M[i][0] = i* delta;
	for (int j = 0; j <=n; ++j)
		M[0][j] = j* delta;

	for (int j = 1; j <=n; ++j)  // para cada letra da palavra str2
		for (int i = 1; i <=m; ++i)  // para cada letre da palavra st1
			M[i][j] = MIN(alpha(i-1,j-1)+M[i-1][j-1], delta+M[i-1][j], delta+M[i][j-1]);			

	return M[m][n];
}



int main(int argc, char const *argv[])
{
	printf("%s *** %s \n", str1, str2);

	printf("O custo mínimo do alinhamento entre %s e %s eh = %d\n", str1, str2, alin(tstr1,tstr2));
	printM();

	return 0;
}
