#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <algorithm>
#include "containers.h"

using namespace std;

//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
private:
	int V;
	vector<list<int>> adj;
	vector <bool> visitados;

public:
	set<int> vertices;
	//Construtor
	Graph(int V){
		this->V = V;
		adj.resize(V);
	}
	//Função para adicionar arestas
	void adicionarAresta(int a, int b){
		//Adiciona b à lista de a
		adj[a].push_back(b);

		//Adiciona a e b a lista de vertices
		vertices.insert(a);
		vertices.insert(b);
	}

	void BFS(int raiz, int **matrix){
		//Cria uma fila para BFS e insere o primeiro elemento
		list<int> queue;
		queue.push_back(raiz);

		//Marca todos vértices como
		//não visitados
		visitados.resize(V, false);

		int distancia = 0;
		bool nivel = true;
		while(!queue.empty()){	
			//Retira vértice da lista e imprime
			int vertice = queue.front();
			queue.pop_front();
			visitados[vertice] = true;

			//Como a busca é feita através de níveis,
			//deve-se incrementar a distância percorrida apenas
			//quando um novo nível for alcançado
			if(nivel){
				distancia++;
				nivel = false;
			} 

			//Pega todos os vértices adjacentes.
			//Se algum não tiver sido visitado,
			//marca como visitado e coloca-o
			//na fila
			for(auto adjacent: adj[vertice]){
				if(!visitados[adjacent]){
					visitados[adjacent] = true;
					queue.push_back(adjacent);
					nivel = true;
					//Grava a distância na matriz
					matrix[raiz][adjacent] = distancia;
					matrix[adjacent][raiz] = distancia;
				}
			}
		}
	}

	int searchCycle(int raiz){
		//Marca todos os vértices como não visitados
		visitados.resize(V, false);

		//Cria uma pilha para a DFS (FIFO)
		stack<int> pilha;

		//Insere o vértice atual na pilha
		pilha.push(raiz);

		//Conta o número de vertices para cada componente
		while(!pilha.empty()){
			//Exclui um vértice da pilha e o imprime
			int vertice = pilha.top();
			pilha.pop();
			stack<int> copy = pilha;
			if(printStack(copy, vertice)) return true;

			//Marca o vértice como visitado
			if(!visitados[vertice]){
				visitados[vertice] = true;
				vertices.erase(vertice);
			}
			//Para todos os vértices adjacentes,
			//caso não tenha sido visitado, coloca
			//na pilha
			for(auto adjacent: adj[vertice])
				if(!visitados[adjacent])
					pilha.push(adjacent);
		}
		return false;
	}
};

int main(){
	//A string será utilizada para absorver lixo da leitura; arquivo para o nome do arquivo
	string arquivo;
	char s[20];
	//Abre o arquivo para leitura
	cin >> arquivo;

	//Número de vértices
	int V = 0;

	ifstream file(arquivo.c_str());
	file >> s >> V;
	file >> s;
	//Cria um grafo com V vértices
	Graph g(V);
	int a, b;
	//Faz a leitura dos vértices a e b ligados
	while(file >> a >> b){
		//É subtraido o valor 1 pois quero trabalhar com
		//índice 0
		a--; b--;
		// cout << a << ";" << b << endl;
		g.adicionarAresta(a, b);
	}

	vector<int> vecContagem;

	if(g.searchCycle(*g.vertices.find(0)))
		cout << "S";
	else
		cout << "N";



	return 0;
}
