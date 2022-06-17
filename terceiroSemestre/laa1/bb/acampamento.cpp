#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int vet[1000];
int n,k;


/*
A funcao retorna TRUE se a caminhada foi muito comprida, portanto sobraram noites pra dormir
OU se a caminha foi exata....
retorna FALSE, caso contrario...
*/

bool funcao(int mid){
	int ac = 0;
	int k_aux = k;
	for (int i = 0; i <= n; ++i){
		ac += vet[i];
		if (ac > mid){
			k_aux--;
			if (k_aux < 0 || vet[i] > mid)
				return false;
			ac = vet[i];
		}
	 } 
	return true;  /// signfica que a caminha eh longa e sobraram noites...
}


int passeio(int l, int h){
	int mid;
	bool result;
	

	while(h - l >= 0) {  // enquanto a diferenca entra min e max for
		mid = (l+h)/2;
		printf("l = %d *** h = %d **** mid = %d\n", l, h, mid);
		//printf("l = %d *** h = %d **** mid = %d\n", l, h, mid);
		result  = funcao (mid);
		printf("%d\n", result);
		if (result) // andei demais.... sobraram noteis..
			h = mid-1;
		else l = mid+1;
		printf("posterior >>> l = %d *** h = %d **** mid = %d\n", l, h, mid);
	}
	
	return funcao(l) ? l : h;

}


/*
double prestacaoR(double l, double h, double valor, int parc){
	double mid;
	double result;
	

	if (h - l > ERRO) {  // enquanto a diferenca entra min e max for maior que o erro
		mid = (l+h)/2.0;
		printf("l = %f *** h = %f **** mid = %f\n", l, h, mid);
		result  = funcao(mid, valor, parc);
		if (result > 0) // a prestacao eh muito baixa...
			return prestacaoR(mid, h, valor, parc);
		else return prestacaoR(l, mid, valor, parc);
	}

	return h;

}
*/

int main(int argc, char const *argv[])
{

	cin >> n >> k;
	int sum = 0;

	for (int i = 0; i <= n; ++i){
		cin >> vet[i];
		sum += vet[i];
	}


	printf("A distancia a caminha eh = %d\n", passeio(0,sum));
	return 0;
}