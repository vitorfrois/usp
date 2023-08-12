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

int delta = 2;  // GAP


//int minimo(int x, int y, int z){
//    return min(min(x, y), z);
//}


int alpha(int i, int j){   // a penalizaaco de uma TROCA preco = 1 (se c1 e c2 forem vogais OU se forem consoantes)
	int res;
	char c1 = str1[i];
	char c2 = str2[j];
	if (c1 == c2)
	  res = 0;
    else if ( (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')  && 
		 (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u') )
		res =  10;
	else if ( !(c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')  && 
		 !(c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u') )
			res = 1;
		 else res = 3;

	//printf("%c ** %c === res = %d\n", c1, c2, res);
	return res;
}

int alin(int i, int j){
	
	if (i == 0)
		return j*delta;
	if (j == 0)
		return i*delta;

	return MIN(alpha(i-1,j-1)+alin(i-1,j-1), delta+alin(i-1,j), delta+alin(i,j-1));

}



int main(int argc, char const *argv[])
{
	printf("%s *** %s \n", str1, str2);

	printf("O custo mínimo do alinhamento entre %s e %s eh = %d\n", str1, str2, alin(tstr1,tstr2));

	return 0;
}
