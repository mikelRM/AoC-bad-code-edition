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

  cout << "TIEMPOS: " << endl;
  for (int t : t_carreras)
    cout << t << endl;

  cout << endl;

  cout << "DISTANCIAS: " << endl;
  for (int d : d_carreras)
    cout << d << endl;

  archivo.close();

}
