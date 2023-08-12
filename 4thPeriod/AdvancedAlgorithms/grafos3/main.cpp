#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define MAXV 100 
#define INF 2147483646

void printMatrix(int **matrix, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void printList(list<int> const &list){
	cout << "(";
    for (auto const &i: list) {
        cout << i << ',';
    }
	cout << ")" << endl;
}

//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
	int V; 
	vector<list<int>> adj;
private:
	//Construtor
	vector <bool> visited;
	vector<vector<int>> capacity;
	
public:
	Graph(int V){
		this->V = V;
		adj.resize(V);
		visited.resize(V, false);
		this->capacity.resize(V, vector<int>(V, 0));
	}
	//Função para adicionar arestas
	void adicionarAresta(int a, int b, int weight){
		//Adiciona b à lista de a
		adj[a].push_back(b);
		adj[b].push_back(a);
		this->capacity[a][b] += weight;
		this->capacity[b][a] += weight;
	}

	vector<int> BFS(int source, int sink){
		//Cria uma fila para BFS e insere o primeiro elemento
		list<int> queue;
		queue.push_back(source);
		//Marca todos vértices como
		//não visited
		fill(visited.begin(), visited.end(), false);
		visited[source] = true;

		vector<int> prev(V, -1);
		while(!queue.empty()){	
			//Retira vértice da lista e imprime
			int vertice = queue.front();
			queue.pop_front();

			//Pega todos os vértices adjacentes.
			//Se algum não tiver sido visitado,
			//marca como visitado e coloca-o
			//na fila
			for(auto adjacent: adj[vertice]){
				int edgeCapacity = this->capacity[vertice][adjacent];
				bool adjVisited = visited[adjacent];
				// cout << capacity[vertice][adjacent] << " & " << visited[adjacent] << " ";
				if(edgeCapacity > 0 && !adjVisited){
					//visit the adjacent vertice
					visited[adjacent] = true;

					//add vertice to the queue
					queue.push_back(adjacent);
					
					//add to the prev list
					prev[adjacent] = vertice;

					if(adjacent == sink)
						return prev;
				}
			}
		}
		return prev;
	}
    
	int edmondsKarpAlgorithm(int src, int dst){
		vector<int> prev = BFS(src, dst);
		if(prev[dst] == -1){
			return 0;
		}
		
		int bottleNeck = INF;
		for(int edge = dst; prev[edge] != -1; edge = prev[edge])
			bottleNeck = min(bottleNeck, this->capacity[prev[edge]][edge]);

		// cout << bottleNeck << "bn";

		for(int edge = dst; prev[edge] != -1; edge = prev[edge]){
			this->capacity[prev[edge]][edge] -= bottleNeck;
		}
		return bottleNeck;
	}

	int edmondsKarp(int src, int dst){
		int maxFlow = 0, flow;
		do{
			flow = edmondsKarpAlgorithm(src, dst);
			maxFlow += flow;
		}while(flow != 0);
		return maxFlow;
	}

};

int main(){
    int V, network = 1;
	while(true){
		cin >> V;
		if(V == 0)
			break;
		Graph g = Graph(V);
		int src, dst, edges;
		cin >> src >> dst >> edges;
		src--; dst--;
		for(int i = 0; i < edges; i++){
			int a, b, weight;
			cin >> a >> b >> weight;
			a--; b--;
			g.adicionarAresta(a, b, weight);
		}
		int bottleNeck = g.edmondsKarp(src, dst);
		if(network != 1) cout << endl;
		printf("Network %d\n", network++);
		printf("The bandwidth is %d.\n", bottleNeck);
	}
	return 0;
}
