#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
  vector<vector<long>> historias;
  ifstream archivo ("part1.in");
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
  vector<vector<long>> ultimos_numeros;
  for (vector<long> hist : historias) {
    ultimos_numeros.push_back({});
    while (hist.size() > 1) {
      bool todo_ceros = true;
      for (int i = 0; i < hist.size() - 1; i++) {
	hist[i] = hist[i+1] - hist[i];
	todo_ceros = (hist[i] == 0) ? todo_ceros : false;
      }
      ultimos_numeros.back().push_back(hist.back());
      hist.pop_back();
      if (todo_ceros) break;
    }
  }

  long suma = 0;
  for (auto const& ult : ultimos_numeros)
    suma = suma + accumulate(ult.begin(), ult.end(), 0);

  cout << "La respuesta de la parte 1 es: " << suma << endl;
  
}
