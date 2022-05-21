#include <iostream>
#include <vector>
#include <list>

using namespace std;

//Essa classe representa um grafo usando lista de adjacência.
class Graph{
	//Número de vértices
	int V; 
	
	vector<list<int>> adj;

	//Construtor
public:
	Graph(int V){
		this->V = V;
		adj.resize(V);
	}
	//Função para adicionar arestas
	void adicionarAresta(int a, int b){
		//Adiciona b à lista de a
		adj[a].push_back(b);
	}

	void BFS(int s, int **matrix){
		//Marca todos vértices como
		//não visitados
		vector <bool> visitados;
		visitados.resize(V, false);

		//Cria uma fila para BFS
		list<int> queue;

		//Marca o nó atual como 
		visitados[s] = true;
		queue.push_back(s);

		int distancia = 0;
	
		recursive()

		while(!queue.empty()){
			//Retira vértice da lista e imprime
			s = queue.front();
			cout << s << " ";
			queue.pop_front();

			//Pega todos os vértices adjacentes.
			//Se algum não tiver sido visitado,
			//marca como visitado e coloca-o
			//na fila
			distancia++;
			for(auto adjacent: adj[s]){
				if(!visitados[adjacent]){
					cout << "i";
					visitados[adjacent] = true;
					queue.push_back(adjacent);
					// distancia++;
					matrix[s][adjacent] = distancia;
					matrix[adjacent][s] = distancia;
				}else{
					cout << "u";
				}
			}
		}
		cout << endl;
	}

	void recursive(queue<int> &queue, vector<bool> &visitados){
		if(queue.empty())
			return;

		int v = queue.front();
		queue.pop();
		cout << v << " ";

		for(auto adjacent: adj[s]){
			if(!visitados[adjacent]){
				visitados[adjacent] = true;
				queue.push_back(adjacent);
			}
		}
		recursive();

	}


};

int main(){
	//A string será utilizada para absorver lixo da leitura; arquivo para o nome do arquivo
	string arquivo;
	char s[20];
	//Abre o arquivo para leitura
	cout << "Insira o nome do arquivo a ser lido: ";
	cin >> arquivo;
	arquivo = ".pajek/" + arquivo;

	FILE *fp = fopen(arquivo.c_str(), "r");
	//Número de vértices
	int V = 0;
	fscanf(fp, "%s %d", s, &V);
	fscanf(fp, "%s", s);
	cout << "v = " << V << endl;
	//Cria um grafo com V vértices
	Graph g(V);
	int a = 0, b;
	for(int i = 1; i < V; i++){
		//Faz a leitura dos vértices a e b ligados
		fscanf(fp, "%d %d", &a, &b);
		//É subtraido o valor 1 pois quero trabalhar com
		//índice 0
		g.adicionarAresta(--a, --b);
		g.adicionarAresta(b, a);
		cout << a << " " << b << endl;
	}

	int **matrix = new int*[V];
	for(int i = 0; i < V; i++)
		matrix[i] = new int[V];

	cout << "bfs = ";
	for(int i = 0; i < V; i++)
		g.BFS(i, matrix);
	
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++)
			cout << matrix[i][j];
		cout << endl;
	}

	fclose(fp);
	return 0;

}
