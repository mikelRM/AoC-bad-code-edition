#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

long contar_filas_espejo (vector<string> &mapa) {
  long resultado = 0;
  int n_filas = mapa.size(), n_columnas = mapa.front().size();
  for (int i = 0; i < n_filas; ++i) {
    int j_max = min(i, n_filas - i);
    bool i_es_espejo = true;
    for (int j = 0; j < j_max; ++j) {
      if (mapa[i+j] != mapa[i-j-1])
	i_es_espejo = false;
    }

    if (i_es_espejo)
      resultado += i;    
  }
  return resultado;
}


int main()
{
  ifstream archivo("input.in");
  string linea;

  vector<vector<string>> lista_de_mapas = {{}};
  while (getline(archivo, linea)) {
    if (linea == "") {
      lista_de_mapas.push_back({});
    } else {
      lista_de_mapas.back().push_back(linea);
    }
  }

  long suma = 0;
  for (vector<string> mapa : lista_de_mapas) {
    vector<string> mapa_t;
    for (int j = 0; j < mapa.front().size(); j++) {
      mapa_t.push_back({});
      for (int i = 0; i < mapa.size(); i++) {
	mapa_t.back() += mapa[i][j];
      }
    }

    suma = suma + 100 * contar_filas_espejo(mapa) + contar_filas_espejo(mapa_t);
  }

  cout << "La respuesta a la parte 1 es: " << suma << endl;
  
  archivo.close();
}
