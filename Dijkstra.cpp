
/**
 * Universidad Complutense de Madrid.
 * Robótica.
 * Grupo A 2021-2022.
 * Profesor:
 * 	-Maroto Ortega, Victor Manuel.
 *
 * Algoritmo de Dijkstra
 *
 * @author
 * 	-Rodríguez Pereira, Diego Alejandro.
 *
 */

/*
* Implementación del algoritmo de Dijkstra que encuentra el camino
* más corto (o de menor distancia) desde un nodo inicial en un grafo
* dirigido.
*
* Complejidad en el tiempo: O(n^2) siendo n el número de vertices en el grafo.
*
*/

#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>
#include <vector>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <string>

using namespace std;

#define MAXV 1000

class EdgeNode {
public:
	int key;
	int weight;
	EdgeNode *next;
	EdgeNode(int, int);
};

EdgeNode::EdgeNode(int key, int weight) {
	this->key = key;
	this->weight = weight;
	this->next = NULL;
}

class Graph {
	bool directed;
public:
	EdgeNode *edges[MAXV + 1];
	Graph(bool);
	~Graph();
	void insert_edge(int, int, int, bool);
	void print();
};

Graph::Graph(bool directed) {
	this->directed = directed;
	for (int i = 1; i < (MAXV + 1); i++) {
		this->edges[i] = NULL;
	}
}

Graph::~Graph() {
	//TODO
}

void Graph::insert_edge(int x, int y, int weight, bool directed) {
	if (x > 0 && x < (MAXV + 1) && y > 0 && y < (MAXV + 1)) {
		EdgeNode *edge = new EdgeNode(y, weight);
		edge->next = this->edges[x];
		this->edges[x] = edge;
		if (!directed) {
			insert_edge(y, x, weight, true);
		}
	}
}

void Graph::print() {
	for (int v = 1; v < (MAXV + 1); v++) {
		if (this->edges[v] != NULL) {
			cout << "Vertex " << v << " has neighbors: " << endl;
			EdgeNode *curr = this->edges[v];
			while (curr != NULL) {
				cout << curr->key << endl;
				curr = curr->next;
			}
		}
	}
}

void init_vars(bool discovered[], int distance[], int parent[]) {
	for (int i = 1; i < (MAXV + 1); i++) {
		discovered[i] = false;
		distance[i] = std::numeric_limits<int>::max();
		parent[i] = -1;
	}
}

void dijkstra_shortest_path(Graph *g, int parent[], int distance[], int start) {

	bool discovered[MAXV + 1];
	EdgeNode *curr;
	int v_curr;
	int v_neighbor;
	int weight;
	int smallest_dist;

	init_vars(discovered, distance, parent);

	distance[start] = 0;
	v_curr = start;

	while (discovered[v_curr] == false) {

		discovered[v_curr] = true;
		curr = g->edges[v_curr];

		while (curr != NULL) {

			v_neighbor = curr->key;
			weight = curr->weight;

			if ((distance[v_curr] + weight) < distance[v_neighbor]) {
				distance[v_neighbor] = distance[v_curr] + weight;
				parent[v_neighbor] = v_curr;
			}
			curr = curr->next;
		}

		//Coloca el siguiente actual vertice al vercite con la menor distancia/coste
		smallest_dist = std::numeric_limits<int>::max();
		for (int i = 1; i < (MAXV + 1); i++) {
			if (!discovered[i] && (distance[i] < smallest_dist)) {
				v_curr = i;
				smallest_dist = distance[i];
			}
		}
	}
}

void print_shortest_path(int v, int parent[]) {

	if (v > 0 && v < (MAXV + 1) && parent[v] != -1) {
		cout << parent[v] << " ";
		print_shortest_path(parent[v], parent);
	}
}

void print_distances(int start, int distance[]) {
	for (int i = 1; i < (MAXV + 1); i++) {
		if (distance[i] != std::numeric_limits<int>::max()) {
			cout << "Camino mas corto desde '" << start << "' hasta '" << i << "' es de coste: " << distance[i] << endl;
		}
	}
}

void read_file(unsigned int numNodos, Graph *g) {

	vector<vector<pair<int, int>>> nodosVecinos;

	for (int j = 0; j < numNodos; j++) {

		unsigned int numAristas;
		std::cin >> numAristas;
		vector<pair<int, int>> vecinos;
		nodosVecinos.push_back(vecinos);

		// Resolvemos
		int aux1, aux2;
		for (int i = 0; i < numAristas; i++) {

			cin >> aux1;
			cin >> aux2;

			g->insert_edge(j + 1, aux1, aux2, false);
			pair<int, int> p(aux1, aux2);
			nodosVecinos[j].push_back(p);
		}
	}

	for (int i = 0; i < numNodos; i++) {
		cout << "Nodo: " << (i + 1) << ". ";
		for (int j = 0; j < nodosVecinos[i].size(); j++) {
			cout << "ar: " << nodosVecinos[i][j].first << ", cost: " << nodosVecinos[i][j].second << ". ";
		}
		cout << "\n";
	}

	/*g->insert_edge(1, 2, 4, false);
	g->insert_edge(1, 3, 1, false);
	g->insert_edge(3, 2, 1, false);
	g->insert_edge(3, 4, 5, false);
	g->insert_edge(2, 4, 3, false);
	g->insert_edge(2, 5, 1, false);
	g->insert_edge(4, 5, 2, false);*/
}

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

inline bool exists_file(const string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main() {

	Graph *g = new Graph(false);
	int parent[MAXV + 1];
	int distance[MAXV + 1];
	int start = 1;

	char fichero[60];
	cout << "Si no desea introducir ningun nombre de fichero, pulse la tecla 'ENTER'\n";
	cout << "Escribe el nombre del fichero: ";
	cin.getline(fichero, 60);
	cout << "El fichero es: " << fichero << "\n\n";


	int a_size = sizeof(fichero) / sizeof(char);
	string caso = convertToString(fichero, a_size);

	if (!exists_file(caso)) {
		caso = "casos.txt";
	}

#ifndef DOMJUDGE
	//std::ifstream in("casos2.txt");
	std::ifstream in(caso);
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	unsigned int numNodos;
	cin >> numNodos;

	read_file(numNodos, g);


	dijkstra_shortest_path(g, parent, distance, start);
	//imprime el camino más corto (o de menor distancia) desde el vertice ini a fin
	cout << "\nEl camino mas corto es pasando por los siguientes vertices: \n";
	cout << numNodos << " ";
	print_shortest_path(numNodos, parent);
	cout << "\n\n";
	print_distances(start, distance);

	delete g;

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}