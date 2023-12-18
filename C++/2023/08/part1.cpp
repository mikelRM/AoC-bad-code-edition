#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

map<string, map<char, string>> mapa;

int main ()
{
  ifstream archivo;
  string linea, instruccion;

  archivo.open("part1.in");

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

  string nodo = "AAA";
  int pasos = 0;

  while (nodo != "ZZZ")
    for (char letra : instruccion) {
      nodo = mapa[nodo][letra];
      pasos++;
    }

  cout << "La respuesta a la parte 1 es: " << pasos << endl;
}
