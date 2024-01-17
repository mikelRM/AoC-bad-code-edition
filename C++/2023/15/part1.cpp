#include <iostream>
#include <fstream>
#include <string>

using namespace std;

long algoritmo_hash (string const& s) {
  long valor = 0;
  for (char const& c : s)
    valor = ((valor + int(c)) * 17) % 256;
  return valor;
}

int main()
{
  ifstream archivo("input.in");
  long suma = 0;

  string linea;
  getline(archivo, linea);
  linea = linea + ",";

  int i_coma;
  while (linea != "") {
    i_coma = linea.find(",");
    suma = suma + algoritmo_hash(linea.substr(0, i_coma));
    linea = linea.substr(i_coma + 1);
  }

  cout << "El resultado de la parte 1 es: " << suma << endl;
}
