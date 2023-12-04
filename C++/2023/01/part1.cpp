#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  ifstream archivo;
  string linea, primero, ultimo;
  int suma;
  bool primero_vacio;
  
  archivo.open("part1.in");

  suma = 0;
  while (getline(archivo, linea)) {
    primero_vacio = true;
    for (char c : linea) {
      if (not isdigit(c)) {
	continue;
      }

      if (primero_vacio) {
	primero = c;
	primero_vacio = false;
      }	
      ultimo = c;
    }
    suma = suma + stoi(primero + ultimo);
  }
  cout << "La respuesta de la parte 1: " << suma << endl;
  archivo.close();
}
