#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

#define MAX 100

int vet[MAX];
int MEMO[MAX];


void printVET(int n){
	for (int i = 0; i < n; ++i){
		printf("%d ", MEMO[i]);
	}
	printf("\n");
}

int lisREC(int i, int &lmax){
	if (i==0)
		return 1;

	int maior = 1;
	for (int j=i-1; j>=0; --j){
		int res = lisREC(j,lmax)+1;
		if (vet[j] < vet[i])
			maior = max(res,maior);
	}

	if (lmax < maior)
		lmax = maior;

	return maior;

}


int lisRECPD(int i, int &lmax){
	if (i==0)
		return 1;

	if (MEMO[i] != -1)
		return MEMO[i];

	int maior = 1;
	for (int j=i-1; j>=0; --j){
		int res = lisRECPD(j,lmax)+1;
		if (vet[j] < vet[i])
			maior = max(res,maior);
	}
	MEMO[i] = maior;

	if (lmax < maior)
		lmax = maior;

	return MEMO[i];

}


int lis(int n){
	
	int lmax = 1;

	for (int i = 1; i <=n; ++i){
		MEMO[i] = 1;
		for (int j=i-1; j>=0; --j){
			int res = MEMO[j]+1;
			if (vet[j] < vet[i])
				MEMO[i] = max(res,MEMO[i]);
		}
		if (lmax < MEMO[i])
		lmax = MEMO[i];
	}

	return lmax;
}

int main(int argc, char const *argv[])
{
	int n;

	int lmax = 1; 
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> vet[i];
	
	printf("A maior subcadeia crescente eh %d\n", lisREC(n-1, lmax));
	printf("O valor correto é o maior dos maiores %d\n", lmax);

	memset(MEMO, -1, sizeof MEMO);
	printf("A maior subcadeia crescente eh (REC PED) %d\n", lisRECPD(n-1, lmax));
	printf("O valor correto é o maior dos maiores (REC PED) %d\n", lmax);
	printVET(n);

	MEMO[0] = 1;
	printf("A maior subcadeia crescente eh (PD) %d\n", lis(n-1));
	printVET(n);
	return 0;
}