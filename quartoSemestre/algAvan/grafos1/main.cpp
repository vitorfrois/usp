#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include <math.h>

typedef long long int lli;
lli INF = 10e9+1;
using namespace std;

void imprimeEspaco(int n){
    for(int i = 0; i < n; i++)
        cout << " ";
}

//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
private:
	lli V;
	vector <bool> visitados;

public:
	vector<list<pair<lli, lli> > > adj;
	set<int> vertices;
	//Construtor
	Graph(lli V){
		this->V = V;
		adj.resize(V);
        visitados.resize(V);
	}

	//Função para adicionar arestas
	void adicionarAresta(int a, int b, lli distancia){
		//Adiciona b à lista de a e vice-versa

		adj[a].push_back(make_pair(b, distancia));
		adj[b].push_back(make_pair(a, distancia));

		//Adiciona a e b a lista de vertices
		vertices.insert(a);
		vertices.insert(b);
	}

    vector<lli> dijkstra(int raiz){
        //No início do algoritmo, seta todas as distâncias, exceto a do valor inserido, 
        //para infinito.
        vector<lli> distancias(V, INF);
        distancias[raiz] = 0;
        //Seta todos vertices como não visitados
        fill(visitados.begin(), visitados.end(), false);
        priority_queue <pair<lli, lli>, vector<pair<lli, lli> >, greater<pair<lli, lli> > > pq;
        pq.push(make_pair(distancias[raiz], raiz));
        while(!pq.empty()){
            //extrai o vertice com menor distância da fila de prioridade
            pair<lli, lli> p = pq.top(); 
            lli u = p.second;
            pq.pop();
            if(visitados[u] == false){
                //marca o vertice atual como visitado
                visitados[u] = true;
                for(auto adjacente : adj[u]){
                    //pega o vértice adjacente e o custo
                    int v = adjacente.first;
                    lli distancia = adjacente.second;
                    //executa o relaxamento
                    if(distancias[v] > (distancias[u] + distancia)){
                        //atualiza a distância de v e insere na fila
                        distancias[v] = distancias[u] + distancia;
                        pq.push(make_pair(distancias[v], v));
                    }
                }
            }
        }

        return distancias;
    }
};

int main(){ 
	//Número de vértices
	int V, E, queries;
    cin >> V >> E >> queries;
    
	//Cria um grafo com V vértices
	Graph g(V);
	//Faz a leitura dos vértices a e b ligados
    int a, b;
    lli c;

	for(int i = 0; i < E; i++){
        cin >> a >> b >> c;
		//É subtraido o valor 1 pois quero trabalhar com
		//índice 0
		a--; b--;
		g.adicionarAresta(a, b, c);
	}
    

    
    vector<lli> matrizDistancias[V];
    vector<lli> init(V, -1);
    for(int i = 0; i < V; i++)
        matrizDistancias[i] = init;

    for(int i = 0; i < queries; i++){
        cin >> a >> b;
        a--; b--;

        if(matrizDistancias[a][b] == -1)
            matrizDistancias[a] = g.dijkstra(a);
        lli dist = matrizDistancias[a][b];

        if(dist == INF)
            cout << -1;
        else
            cout << dist;
        cout << endl;
    }

    return 0;
}
