#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include <math.h>

#define INF 10e8
using namespace std;

void imprimeEspaco(int n){
    for(int i = 0; i < n; i++)
        cout << " ";
}

//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
private:
	int V;
	vector <bool> visitados;

public:
	vector<list<pair<int, int> > > adj;
	set<int> vertices;
	//Construtor
	Graph(int V){
		this->V = V;
		adj.resize(V);
        visitados.resize(V);
	}

	//Função para adicionar arestas
	void adicionarAresta(int a, int b, int distancia){
		//Adiciona b à lista de a
		adj[a].push_back(make_pair(b, distancia));

		//Adiciona a e b a lista de vertices
		vertices.insert(a);
		vertices.insert(b);
	}

    vector<int> dijkstra(int raiz){
        //No início do algoritmo, seta todas as distâncias, exceto a do valor inserido, 
        //para infinito.
        vector<int> distancias(V, INF);
        distancias[raiz] = 0;
        //Seta todos vertices como não visitados
        fill(visitados.begin(), visitados.end(), false);
        priority_queue <pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(distancias[raiz], raiz));
        while(!pq.empty()){
            //extrai o vertice com menor distância da fila de prioridade
            pair<int, int> p = pq.top(); 
            int u = p.second;
            pq.pop();
            if(visitados[u] == false){
                //marca o vertice atual como visitado
                visitados[u] = true;
                for(auto adjacente : adj[u]){
                    //pega o vértice adjacente e o custo
                    int v = adjacente.first;
                    int distancia = adjacente.second;
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
	int a, b, c;
	//Faz a leitura dos vértices a e b ligados
	while(file >> a >> b >> c){
		//É subtraido o valor 1 pois quero trabalhar com
		//índice 0
		a--; b--;
		g.adicionarAresta(a, b, c);
	}
    
    vector<int> matrizDistancias[V];
    
    for(int vertice : g.vertices)
        matrizDistancias[vertice] = g.dijkstra(vertice);
    
    //Um pequeno script para calcular o tamanho máximo em cada linha da matriz de distâncias
    int espacos[V];
    for(int i = 0; i < V; i++)
        espacos[i] = 0;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            int resultado = (int) log10(matrizDistancias[i][j]);
            if(resultado > espacos[j])
                espacos[j] = resultado;
        }
    }

    //Printa as distâncias calculadas pelo algoritmo de dijkstra
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++)
            printf("%*d ", espacos[j]+1, matrizDistancias[i][j]);
        
        cout << endl;
    }


    return 0;
}