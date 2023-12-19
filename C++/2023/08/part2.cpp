// IDEA:
//  
// Para cada nodo inicial, buscar el primer punto en el que se cumpla
// la condición de llegar a un resultado que termine en **Z.
// Posteriormente se busca el periodo con el que se repite dicha
// respuesta.  Finalmente se busca el paso en el que este ciclo
// coincidiría para todos los nodos iniciales mediante una búsqueda de
// mínimo común múltiplo generalizada. 
  
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

int main ()
{
  map<string, map<char, string>> mapa;
  ifstream archivo;
  string linea, instruccion;

  archivo.open("part2.in");

  // La primera linea da la instruccion y la segunda está vacía.
  getline(archivo, instruccion);
  getline(archivo, linea);

  // ´Parse´-amos el mapa
  int i_sep;
  while (getline(archivo, linea)) {
    mapa.insert({
		 linea.substr(0, 3),
		 {{'L', linea.substr(7, 3)},
		  {'R', linea.substr(12, 3)}}
      });
  }

  // Buscamos los nodos de inicio: los de la forma **A
  vector<string> nodos;
  for (auto const& par : mapa)
    if (par.first[2] == 'A')
      nodos.push_back(par.first);
  int pasos = 0;

  // Búsqueda del inicio del ciclo y su periodo
  vector<long> desp_ciclo, tamaño_ciclo;
  for (string nodo : nodos) {
    cout << "El primer nodo acabado en 'Z' de " << nodo << " es: ";
    long pos = 0;
    do {
      for (char c : instruccion) {
	pos++;
	nodo = mapa[nodo][c];
	if (nodo[2] == 'Z') break;
      }
    } while (nodo[2] != 'Z');
    
    cout << nodo << endl
	 << "\tOffset: " << pos << " pasos";

    desp_ciclo.push_back(pos);

    // Ahora medimos el periodo del ciclo
    pos = 0;
    string objetivo = nodo;
    do {
      for (char c : instruccion) {
	pos++;
	nodo = mapa[nodo][c];
	//if (nodo == objetivo) break;
	if (nodo[2] == 'Z') break;
      }
    // } while (nodo != objetivo);
    } while (nodo[2] != 'Z');

    cout << "\tPeriodo: " << pos << endl << endl;
    tamaño_ciclo.push_back(pos);
  }

  // Como resulta que el periodo es el mismo que el offset, y además
  // todos son divisibles por el tamaño de la cadena de instrucciones,
  // resultando en NÚMEROS PRIMOS podemos simplemente calcular el
  // m.c.m. de la siguiente forma:
  for (long &x : tamaño_ciclo)
    x = x / instruccion.size();

  long long resultado = 1;
  for (long const& x : tamaño_ciclo)
    resultado *= x;
  
  cout << "El producto de todos los elementos es: " << resultado << endl;
  cout << "Como el tamaño de la cadena es de : " << instruccion.size() << endl;
  cout << "La respuesta a la parte 2 es: " << resultado * instruccion.size() << endl;

}
