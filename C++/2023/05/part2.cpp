#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;
using vec2 = vector<pair<long, long>>;
using vec3 = vector<array<long, 3>>;

vec2 leer_semillas (string linea);
vec2 propagar_rangos (vec2 rangos, vec3 mapa);

int main()
{
  ifstream archivo;
  string linea;
  vec2 rangos, buf_rangos;
  vec3 mapa;

  archivo.open("part2.in");
  while ( getline(archivo, linea) ) {
    // Pasamos de las líneas vacías.
    if ( linea == "")
      continue;

    // Leemos la línea con las semillas.
    if ( linea.find("seeds:") != string::npos ) {
      rangos = leer_semillas(linea);
      continue;
    }

    // Cuando pasamos a la definición del siguiente mapa, se guardan
    // las transformaciones de manera permanente.
    if ( linea.find("map:") != string::npos ) {
      if ( not mapa.empty() )
	rangos = propagar_rangos(rangos, mapa);
      
      mapa.clear();
      continue;
    }

    // Leemos las transformaciones del mapa línea a línea.
    int i_esp = linea.find(" ");
    long base_dest = stol(linea.substr(0, i_esp));
    linea = linea.substr(i_esp+1);
    i_esp = linea.find(" ");
    long base_orig = stol(linea.substr(0, i_esp));
    long rango = stol(linea.substr(i_esp+1));

    mapa.push_back({base_dest, base_orig, rango});    
  }

  // Aquí hay que hacerlo una vez más
  rangos = propagar_rangos(rangos, mapa);
  archivo.close();
  
  return 0;
}


vec2 leer_semillas (string linea) {
  vec2 semillas;
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

    semillas.push_back({stol(base), stol(rango)});

  }
  
  return semillas;  
}


vec2 propagar_rangos (vec2 rangos, vec3 mapa) {
  vec2 buffer;

  // Ordenar los mapas según su base_origen
  sort(mapa.begin(), mapa.end(),
       [](auto &left, auto &right) { return left[1] < right[1]; });
  
  for ( pair<long,long> rango : rangos ) {
    long inicio = 0;
    for ( array<long,3> tr : mapa ) {
      
    }
  }
  return rangos;
}
