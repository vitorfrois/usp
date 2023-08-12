#include <iostream>
#include <cstdio>
#include <cmath>

#define ERRO 0.0001
#define ERRO2 1e-6

using namespace std;


double funcao(double prest, double valor, int parc){
	//return (valor*1.1 - prest)*1.1 - prest;
	double y = valor;
	for (int i = 0; i < parc; ++i)
	 {
	 	y = y*1.1 - prest;
	 } 
	 return y;
}

double funcao2(double prest, double valor, int parc){
	return (valor*1.1 - prest)*1.1 - prest;
}

double prestacao(double l, double h, double valor, int parc){
	double mid;
	double result;
	

	while(h - l > ERRO) {  // enquanto a diferenca entra min e max for maior que o erro
		mid = (l+h)/2.0;
		printf("l = %f *** h = %f **** mid = %f\n", l, h, mid);
		result  = funcao (mid, valor, parc);
		if (result > 0) // a prestacao eh muito baixa...
			l = mid;
		else h = mid;
	}

	return h;

}


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

int main(int argc, char const *argv[])
{
	double l = 0.01;
	double h = 1000.0*1.1;
	int parcelas = 2;
	double valor = 1000.0;

	printf("O valor da prestacao eh = %.2f\n", prestacao(l,h,valor, parcelas));
	return 0;
}
