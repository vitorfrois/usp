#include <iostream>
#include <vector>
#include <list>

using namespace std;

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

	void BFS(int raiz, int **matrix){
		//Cria uma fila para BFS e insere o primeiro elemento
		list<int> queue;
		queue.push_back(raiz);

		//Marca todos vértices como
		//não visitados
		vector <bool> visitados;
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
};

int main(){
	//A string será utilizada para absorver lixo da leitura; arquivo para o nome do arquivo
	string arquivo;
	char s[20];
	//Abre o arquivo para leitura
	// cout << "Insira o nome do arquivo a ser lido: ";
	cin >> arquivo;
	arquivo = ".pajek/" + arquivo;

	FILE *fp = fopen(arquivo.c_str(), "r");
	//Número de vértices
	int V = 0;
	fscanf(fp, "%s %d", s, &V);
	fscanf(fp, "%s", s);
	// cout << "v = " << V << endl;
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
	}

	int **matrix = new int*[V];
	for(int i = 0; i < V; i++)
		matrix[i] = new int[V];

	for(int i = 0; i < V; i++)
		g.BFS(i, matrix);
	
	printMatrix(matrix, V);

	for(int i = 0; i < V; i++)
		delete [] matrix[i];
	delete [] matrix;
	fclose(fp);
	return 0;

}
