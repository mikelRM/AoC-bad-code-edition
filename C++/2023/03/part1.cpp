#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  const string numeros = "1234567890";
  vector<string> mapa = {};
  
  ifstream archivo("part1.in");
  string linea;
  int n_columnas, n_lineas;
  int j_base, j_min, j_max, i_min, i_max;
  int numero, suma;
  bool cuenta;

  n_lineas = 0;
  while (getline(archivo, linea)) {
    mapa.push_back(linea);
    n_lineas++;
    n_columnas = linea.length();
  }

  suma = 0;
  for (int i = 0; i < n_lineas; i++) {
    linea = mapa[i];
    j_base = 0; j_min = 0; j_max = 0;
    while (j_base < linea.length() - 1) {
      j_min = j_base + linea.substr(j_base).find_first_of(numeros);
      if (j_min < j_base)
	break;
      j_max = j_min + linea.substr(j_min).find_first_not_of(numeros);
      if (j_max <= j_min)
	j_max = linea.length();
      j_base = j_max;

      // Comprobamos si hay símbolos alrededor
      numero = stoi(linea.substr(j_min, j_max-j_min));
      i_min = max(0, i-1);
      i_max = min(i + 1, n_lineas-1);
      j_min = max(0, j_min-1);
      j_max = min(j_max + 1, n_columnas-1);

      cuenta = false;
      if ((mapa[i_min].substr(j_min, j_max-j_min)
	  .find_first_not_of(numeros + ".") < n_columnas)
	  or
	  (mapa[i].substr(j_min, j_max-j_min)
	  .find_first_not_of(numeros + ".") < n_columnas)
	  or 
	  (mapa[i_max].substr(j_min, j_max-j_min)
	   .find_first_not_of(numeros + ".") < n_columnas))
	cuenta = true;

      if (cuenta) {
	suma = suma + numero;
      }
    }
  }

  cout << "La respuesta a la parte 1 es: " << suma << endl;
}
