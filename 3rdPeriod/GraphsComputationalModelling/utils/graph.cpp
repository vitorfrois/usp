#include "graph.h"

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

	void BFS(int raiz){
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
					//Grax[adjacent][raiz] = distancia;
				}
			}
		}
	}

	void DFS(int raiz){
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
	}
};