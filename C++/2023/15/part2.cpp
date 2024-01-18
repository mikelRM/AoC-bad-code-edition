#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int algoritmo_hash (string const& s) {
  int valor = 0;
  for (char const& c : s)
    valor = ((valor + int(c)) * 17) % 256;
  return valor;
}

int main()
{
  ifstream archivo("input.in");

  string linea;
  getline(archivo, linea);
  linea = linea + ",";

  vector<pair<string, int>> cajas[256] = {{}};
  int i_coma;
  while (linea != "") {
    i_coma = linea.find(",");

    string token = linea.substr(0, i_coma);
    linea = linea.substr(i_coma + 1);

    if ((i_coma = token.find("=")) != string::npos) {
      string clave = token.substr(0, i_coma);
      int valor = stoi(token.substr(i_coma + 1));
      vector<pair<string, int>>& caja = cajas[algoritmo_hash(clave)];

      bool clave_en_caja = false;
      for (auto it = caja.begin(); it != caja.end(); ++it) {
	if (it->first == clave){
	  it->second = valor;
	  clave_en_caja = true;
	  break;
	}
      }
      if (!clave_en_caja)
	caja.push_back({clave, valor});
    }
    
    else if ((i_coma = token.find("-")) != string::npos) {
      string clave = token.substr(0, i_coma);
      vector<pair<string, int>>& caja = cajas[algoritmo_hash(clave)];
      
      for (auto it = caja.begin(); it != caja.end(); ++it) {
	if (it->first == clave) {
	  caja.erase(it);
	  break;
	}
      }
    }

    else
      exit;
  }

  long suma = 0;
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < cajas[i].size(); ++j) {
      suma = suma + (i+1)*(j+1)*cajas[i][j].second;
    }
  }
  
  cout << "El resultado de la parte 2 es: " << suma << endl;
}
