#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long distancia(pair<int, int> p1, pair<int, int> p2);
    
int main() 
{
  ifstream archivo ("part1.in");
  string linea;
  vector<vector<bool>> universo;

  // 0. Observación del universo
  while (getline(archivo, linea)) {
    universo.push_back({});
    for (char c : linea) {
      if (c == '.')
	universo.back().push_back(false);
      else if (c == '#')
	universo.back().push_back(true);
      else
	cout << "No sé que es este caracter: " << c << endl;
    }
  }
  
  // 1. Cálculo de su expansión:
  // 1.1. Búsqueda de las filas y las columnas vacías
  int n = universo.size(); 	// nos valemos de que n_filas = n_cols
  vector<int> filas_vacias, columnas_vacias;
  for (int i = 0; i < n; i++) {
    bool f_con_galaxias = false;
    bool c_con_galaxias = false;
    for (int j = 0; j < n; j++) {
      f_con_galaxias = (f_con_galaxias or universo[i][j]);
      c_con_galaxias = (c_con_galaxias or universo[j][i]);
    }
    if (!f_con_galaxias)
      filas_vacias.push_back(i);
    if (!c_con_galaxias)
      columnas_vacias.push_back(i);
  }
  

  // 1.2. Expansión del universo
  vector<bool> vacio(n, false);
  for (auto i = filas_vacias.rbegin(); i != filas_vacias.rend(); i++)
    universo.insert(universo.begin() + *i, vacio);

  for (auto j = columnas_vacias.rbegin(); j != columnas_vacias.rend(); j++)
    for (int i = 0; i < universo.size(); i++)
      universo[i].insert(universo[i].begin() + *j, false);

  
  // 2. Búsqueda de las galaxias
  vector<pair<int, int>> galaxias;
  for (int i = 0; i < universo.size(); i++)
    for (int j = 0; j < universo.front().size(); j++)
      if (universo[i][j])
	galaxias.push_back({i, j});

  // 3. Cálculo de las distancias entre cada par de galaxias
  long suma = 0;
  for (int k = 0; k < galaxias.size(); k++)
    for (int l = k+1; l < galaxias.size(); l++)
      suma = suma + distancia(galaxias[k], galaxias[l]);

  cout << "La respuesta a la parte 1 es: " << suma << endl;
}

long distancia(pair<int, int> p1, pair<int, int> p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
