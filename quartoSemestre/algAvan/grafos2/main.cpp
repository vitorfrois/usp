#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <algorithm>

typedef long long int lli;

typedef struct EDGE{
	lli u, v, weight;
}Edge;

using namespace std;

lli INF = 10e10;


//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
private:
	int V;
	vector<list<pair<lli, lli>>> adj;
	vector <bool> visitados;
	vector<Edge> arestas;

public:
	set<int> vertices;
	//Construtor
	Graph(int V){
		this->V = V;
		adj.resize(V);
	}
	//Função para adicionar arestas
	void adicionarAresta(lli a, lli b, lli distancia){
		//Adiciona b à lista de a
		adj[a].push_back(make_pair(b, distancia));
		//Adiciona a e b a lista de vertices
		vertices.insert(a);
		vertices.insert(b);
		//adiciona nova aresta
		Edge e;
		e.u = a;
		e.v = b;
		e.weight = distancia;
		arestas.push_back(e);
	}

	vector<lli> relaxation(){
		vector<lli> distancias(V, INF);
		distancias[0] = 0;
		//executa o relaxamento V-1 vezes
		for(int j = 1; j < V; j++){
			for(int i = 0; i < (int) arestas.size(); i++){
				if(distancias[arestas[i].u] != INF && distancias[arestas[i].v] > distancias[arestas[i].u] + arestas[i].weight)
					distancias[arestas[i].v] = distancias[arestas[i].u] + arestas[i].weight;
			}
		}
		return distancias;
	}

	bool searchNegativeCycle(){
		vector<lli> distancias = relaxation();

		for(int i = 0; i < (int) arestas.size(); i++){
			if(distancias[arestas[i].u] != INF && distancias[arestas[i].v] > distancias[arestas[i].u] + arestas[i].weight)
				return true;
		}
		return false;
	}
};

int main(){
	//Número de vértices
	int V, E;
    cin >> V >> E;
    
	//Cria um grafo com V vértices
	Graph g(V);
	//Faz a leitura dos vértices a e b ligados
    lli a, b, c;

	for(int i = 0; i < E; i++){
        cin >> a >> b >> c;
		//É subtraido o valor 1 pois quero trabalhar com
		//índice 0
		a--; b--;
		g.adicionarAresta(a, b, c);
	}
    
	if(g.searchNegativeCycle())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
    return 0;
}
