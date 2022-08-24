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

bool checkFalse(vector<bool> vec){
    for(bool i : vec)
        if(i == false)
            return true;
    return false;
}

struct compare {
    constexpr bool operator()(
        pair<int, int> const& a,
        pair<int, int> const& b)
        const noexcept{
        return a.second > b.second;
    }
};

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
		adj[b].push_back(make_pair(a, distancia));

		//Adiciona a e b a lista de vertices 
		vertices.insert(a);
		vertices.insert(b);
	}

    int prim(int raiz){
        vector<int> distancias(V, INF);
        int valorMST = 0;
        int verticeAtual = raiz;
        priority_queue <pair<int, int>, vector<pair<int, int> >, compare > pq;
        do{
            //marca o vertice atual como visitado
            visitados[verticeAtual] = true;
            //adiciona todos as arestas adjacentes a fila de prioridade
            for(auto adjacente : adj[verticeAtual])
                pq.push(adjacente);
            
            //extrai o vertice com menor distância da fila de prioridade
            pair<int, int> p;
            do{
                p = pq.top();
                pq.pop();
            }while(visitados[p.first] == true && !pq.empty()); // é necessário que o vértice ainda não tenha sido visitado
            verticeAtual = p.first;

            //soma o valor da aresta 
            if(!pq.empty())
                valorMST += p.second; 
        }while((checkFalse(visitados) && !pq.empty()));

        return valorMST;
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
        //c é o peso da aresta entre a e b
		g.adicionarAresta(a, b, c);
	}
    cout << g.prim(a);

}