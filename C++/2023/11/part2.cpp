#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

long FACTOR_EXPANSION = 1000000;
long distancia(pair<int, int> p1, pair<int, int> p2, vector<int> f_vac, vector<int> c_vac);
    
int main() 
{
  ifstream archivo ("part2.in");
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
  
  // 1. Búsqueda de las filas y las columnas vacías y de las galaxias.
  int n = universo.size();
  vector<int> filas_vacias, columnas_vacias;
  vector<pair<int, int>> galaxias;
  for (int i = 0; i < n; i++) {
    bool f_con_galaxias = false;
    bool c_con_galaxias = false;
    for (int j = 0; j < n; j++) {
      f_con_galaxias = (f_con_galaxias or universo[i][j]);
      c_con_galaxias = (c_con_galaxias or universo[j][i]);
      if (universo[i][j])
	galaxias.push_back({i, j});
    }
    if (!f_con_galaxias)
      filas_vacias.push_back(i);
    if (!c_con_galaxias)
      columnas_vacias.push_back(i);
  }
  

  // 3. Cálculo de las distancias entre cada par de galaxias
  long suma = 0;
  for (int k = 0; k < galaxias.size(); k++)
    for (int l = k+1; l < galaxias.size(); l++)
      suma = suma + distancia(galaxias[k], galaxias[l], filas_vacias, columnas_vacias);

  cout << "La respuesta a la parte 2 es: " << suma << endl;
}

long distancia(pair<int, int> p1, pair<int, int> p2, vector<int> f_vac, vector<int> c_vac) {
  int f1 = min(p1.first, p2.first);
  int f2 = max(p1.first, p2.first);
  int c1 = min(p1.second, p2.second);
  int c2 = max(p1.second, p2.second);

  long resultado = (f2 - f1) + (c2 - c1);

  // Ahora sumamos los términos de expansión
  for (int cv : c_vac) 
    if ((c1 < cv) and (cv < c2))
      resultado = resultado + (FACTOR_EXPANSION - 1);

  for (int fv : f_vac) 
    if ((f1 < fv) and (fv < f2))
      resultado = resultado + (FACTOR_EXPANSION - 1);

  return resultado;
}
