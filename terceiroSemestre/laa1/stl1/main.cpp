#include <iostream>
#include <stack>

using namespace std;

stack<int> inverter(stack<int> pilha){
	stack<int> pilhaInvertida;
	while(pilha.empty() != true){
		pilhaInvertida.push(pilha.top());
		pilha.pop();
	}	
	return pilhaInvertida;
}

void imprimirPilha(stack<int> pilha){
	while(!pilha.empty()){
		cout << pilha.top() << "\n";
		pilha.pop();
	}
}

stack<int> lerPilha(){
	stack<int> pilha;
	int nElementos, n;
	cin >> nElementos;
	for(int j = 0; j < nElementos; j++){
		cin >> n;
		pilha.push(n);
	}
	return pilha;
}

int main(){
	int nCasos;
	cin >> nCasos;
	for(int i = 0; i < nCasos; i++){
		stack<int> pilha = lerPilha();
		//stack<int> pilhaInvertida = inverter(pilha);
		imprimirPilha(pilha);
		if(i+1 != nCasos) cout << "\n";
	}
	return 0;
}
