#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

vector<pair<long, long>> leer_semillas (string linea);

int main()
{
  ifstream archivo;
  string linea;
  vector<pair<long, long>> rangos, buf_rangos;

  archivo.open("part2.in");
  while ( getline(archivo, linea) ) {
    // Pasamos de las líneas vacías.
    if ( linea == "")
      continue;

    // Leemos la línea con las semillas.
    if ( linea.find("seeds:") != string::npos ) {
      buf_rangos = leer_semillas(linea);
      continue;
    }

    // Cuando pasamos a la definición del siguiente mapa, se guardan
    // las transformaciones de manera permanente.
    if ( linea.find("map:") != string::npos ) {
      rangos = buf_rangos;
      continue;
    }

    // Leemos las transformaciones del mapa línea a línea.
    int i_esp = linea.find(" ");
    long base_dest = stol(linea.substr(0, i_esp));
    linea = linea.substr(i_esp+1);

    i_esp = linea.find(" ");
    long base_orig = stol(linea.substr(0, i_esp));
    
    long rango = stol(linea.substr(i_esp+1));

    // Añadimos los rangos que coincidan con alguna transformación.
    // TO-DO

    // Realizamos un "merge" de todos los rangos en rangos únicos.
    // TO-DO
    
  }
  archivo.close();
  
  return 0;
}


vector<pair<long, long>> leer_semillas (string linea) {
  vector<pair<long, long>> semillas;
  int ii;
  string base, rango;

  ii = linea.find(":");
  linea = linea.substr(ii + 1);
  while ( linea != "") {
    ii = linea.find(" ");
    base = linea.substr(0, ii);
    linea = linea.substr(ii + 1);

    if ( (base == "") or (base == " ") )
      continue;
    
    ii = linea.find(" ");
    rango = linea.substr(0, ii);
    linea = linea.substr(ii + 1);

    if ( ii == string::npos ) {
      rango = linea;
      linea = "";
    }    

    semillas.push_back({ stol(base), stol(rango) });
  }

  return semillas;
  
}
