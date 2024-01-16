#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

long inclinar_y_pesar (vector<string>& mapa)
{
  long peso_total = 0;

  for (int j = 0; j < mapa.front().size(); ++j) {
    int i_obstaculo = -1;
    for (int i = 0; i < mapa.size(); ++i) {
      if (mapa[i][j] == '#')
	i_obstaculo = i;

      if (mapa[i][j] == 'O') {
	mapa[i][j] = '.';
	mapa[i_obstaculo+1][j] = 'O';
	i_obstaculo = i_obstaculo + 1;
	peso_total = peso_total + (mapa.size() - i_obstaculo);
      }
    }
  }

  return peso_total;
}

int main()
{
  ifstream archivo("input.in");
  string linea;

  vector<string> mapa_piedras;
  
  while (getline(archivo, linea)) {
    mapa_piedras.push_back(linea);
  }
  
  long peso_total = inclinar_y_pesar(mapa_piedras);
  cout << "El resultado de la parte 1 es: " << peso_total << endl;
}
