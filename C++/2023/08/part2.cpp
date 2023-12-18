#include <iostream>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

map<string, map<char, string>> mapa;
long long mcm_vector (vector<int> vec);

int main ()
{
  ifstream archivo;
  string linea, instruccion;

  archivo.open("part2.in");

  // La primera linea da la instruccion
  getline(archivo, instruccion);

  // La segunda linea esta vacia
  getline(archivo, linea);

  // Ahora leemos el mapa
  int i_sep;
  while (getline(archivo, linea)) {
    mapa.insert({
		 linea.substr(0, 3),
		 {{'L', linea.substr(7, 3)},
		  {'R', linea.substr(12, 3)}}
      });
  }

  vector<string> nodos;
  for (auto const& par : mapa)
    if (par.first[2] == 'A')
      nodos.push_back(par.first);
  int pasos = 0;

  // Buscar el inicio del ciclo, el tamaño de este y la posición de
  // los elementos que acaban en 'Z' a partir de los elementos
  // precedentes.  Coincide que el elemento que acaba con 'Z' es
  // siempre el último de cada cilo.
  vector<int> el_preceden, el_ciclo, size_el_visitados;
  for (string nodo : nodos) {
    vector<string> nodos_visitados = { nodo };
    while (true) {
      bool salir_del_ciclo = false;
      for (char c : instruccion) {
	nodo = mapa[nodo][c];
  
	size_t idx = find(nodos_visitados.begin(),
			  nodos_visitados.end(), nodo) - nodos_visitados.begin();

	if ( idx < nodos_visitados.size() ) { // Si ya estaba repetido
	  // cout << "EL PRIMERO QUE SE REPITE: " << nodo << endl;
	  // cout << "El segundo elemento: " << nodos_visitados[1] << endl;
	  // cout << "El último del ciclo: " << nodos_visitados.back() << endl;
	  el_preceden.push_back(idx);
	  el_ciclo.push_back(nodos_visitados.size() - idx);
	  size_el_visitados.push_back(nodos_visitados.size());
	  salir_del_ciclo = true;
	  break;
	}
	nodos_visitados.push_back(nodo);
      }
      if (salir_del_ciclo) break;
    }

    cout << "El precede:      " << el_preceden.back() << endl
	 << "Els ciclo:       " << el_ciclo.back() << endl
	 << "Último elemento: " << nodos_visitados.back() << endl
	 << "Tamaño visita:   " << nodos_visitados.size() << endl << endl;
  }

  
  // Comprobar que todos los elementos que preceden a los ciclos son
  // del mismo tamaño. 
  if ((unique(el_preceden.begin(), el_preceden.end()) - el_preceden.begin()) != 1) {
    cout << "ERROR: El número de elementos precediendo a los ciclos no coindice." << endl;
    // exit(1);
  }
    
  cout << "El producto: " << mcm_vector(el_ciclo) << endl;

  cout << "Tamaño de una cadena de instrucciones: " << instruccion.size() << endl;

  cout << "El resultado de la parte 2 es: "
       << mcm_vector(el_ciclo) << endl;
    
}

int mcd (int a, int b) {
  if (b == 0)
    return a;
  return mcd(b, a % b);
}

long long mcm_vector(vector<int> vec) {
  return accumulate(vec.begin(), vec.end(), 1,
		    [](int x, int y) { return (x*y) / mcd(x, y); });
}
