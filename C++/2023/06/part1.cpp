#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
  ifstream archivo;
  string linea, token;

  int ii;
  vector<int> t_carreras, d_carreras;

  archivo.open("part1.in");

  // LEEMOS LOS TIEMPOS
  getline(archivo, linea);
  linea = linea.substr(9);
  while (linea != "") {
    ii = linea.find(" ");
    token = linea.substr(0, ii);
    linea = linea.substr(ii+1);

    if (ii == string::npos)
      linea = "";

    if (token != "")
      t_carreras.push_back(stoi(token));
  }
  
  // LEEMOS LAS DISTANCIAS
  getline(archivo, linea);
  linea = linea.substr(9);
  while (linea != "") {
    ii = linea.find(" ");
    token = linea.substr(0, ii);
    linea = linea.substr(ii+1);

    if (ii == string::npos)
      linea = "";
    
    if (token != "")
      d_carreras.push_back(stoi(token));
  }

  archivo.close();

  long producto = 1;
  int posibilidades_victoria, distancia, velocidad;
  for (int i = 0; i < t_carreras.size(); ++i) {
    posibilidades_victoria = 0;
    for (int t_pres = 1; t_pres < t_carreras[i]; t_pres++) {
      velocidad = t_pres;	// Por mera claridad
      distancia = velocidad * (t_carreras[i] - t_pres);
      if (distancia > d_carreras[i])
	posibilidades_victoria += 1;
    }

    producto = producto * posibilidades_victoria;
  }

  cout << "La respuesta a la parte 1 es: " << producto << endl;
}
