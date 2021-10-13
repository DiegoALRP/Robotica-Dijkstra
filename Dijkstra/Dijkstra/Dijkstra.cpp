#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	// Para la entrada por fichero.
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	unsigned int numNodos;
	cin >> numNodos;
	for (int j = 0; j < numNodos; j++) {

		unsigned int numAristas;
		std::cin >> numAristas;
		// Resolvemos
		int aux;
		for (int i = 0; i < numAristas; ++i) {
			cin >> aux;
			cout << aux;
		}
		cout << "\n";
	}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}