#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
  vector<vector<long>> historias;
  ifstream archivo ("part2.in");
  string linea;

  // Leemos el archivo
  while (getline(archivo, linea)) {
    string token;
    int i_esp;
    historias.push_back({});
    while ( linea != "" ) {
      i_esp = linea.find(" ");
      token = linea.substr(0, i_esp);
      linea = linea.substr(i_esp + 1);
      if (i_esp == string::npos) {
	token = linea;
	linea = "";
      }
      historias.back().push_back(stol(token));
    }
  }
  archivo.close();

  // Resolvemos el problema
  vector<vector<long>> primeros_numeros;
  for (vector<long> hist : historias) {
    primeros_numeros.push_back({});
    while (hist.size() > 1) {
      primeros_numeros.back().push_back(hist[0]);
      bool todo_ceros = true;
      for (int i = 0; i < hist.size() - 1; i++) {
	hist[i] = hist[i+1] - hist[i];
	todo_ceros = (hist[i] == 0) ? todo_ceros : false;
      }
      hist.pop_back();
      if (todo_ceros) break;
    }
  }

  // long suma = 0;
  // for (auto prim : primeros_numeros) {
  //   for (int i = prim.size() - 2; i >= 0; i--)
  //     prim[i] = prim[i] - prim[i+1];
  //   suma = suma + prim[0];
  // }
  // cout << "La respuesta de la parte 2 es: " << suma << endl;

  // Método alternativo al naive que he comentado anteriormente.
  long suma = 0;
  for (auto const& prim : primeros_numeros) {
    suma = suma + accumulate(prim.rbegin(), prim.rend(), 0,
			     [] (long a, long b) { return b - a; });
  }
  cout << "La respuesta de la parte 2 es: " << suma << endl;  

}
