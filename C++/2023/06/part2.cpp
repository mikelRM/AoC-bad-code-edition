#include <cctype>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main ()
{
  ifstream archivo;
  string linea, token;

  int ii;
  long t, d;

  archivo.open("part2.in");

  // LEEMOS EL TIEMPO
  getline(archivo, linea);
  token = "";
  for (char c : linea) {
    if (isdigit(c))
      token = token + c;
  }
  t = stol(token);

  // LEEMOS LA DISTANCIA
  getline(archivo, linea);
  token = "";
  for (char c : linea) {
    if (isdigit(c))
      token = token + c;
  }
  d = stol(token);

  // Buscamos las raíces
  double t1 = (t + sqrt(t*t - 4. * d)) / 2.0;
  double t2 = (t - sqrt(t*t - 4. * d)) / 2.0;

  cout << "La respuesta a la parte 2 es: " << long(t1) - long(t2) << endl;
}
