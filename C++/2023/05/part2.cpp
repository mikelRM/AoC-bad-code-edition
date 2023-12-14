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

  long minimo = rangos[0].first;
  for ( pair<long, long> el : rangos)
    minimo = (el.first < minimo) ? el.first : minimo;

  cout << "La respuesta a la parte 2 es: " << minimo << endl;
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

  // Propagamos los rangos 
  for ( pair<long,long> rango : rangos ) {
    long inicio = rango.first;
    for ( array<long,3> tr : mapa ) {
      if ( (tr[1] + tr[2] - 1) < inicio )
	continue;
      
      if ( tr[1] > (rango.first + rango.second - 1) )
	continue;

      // Si estamos aquí, los rangos coinciden
      if (tr[1] > inicio) {
	buffer.push_back({ inicio, tr[1] - inicio});
	inicio = tr[1];
      }

      long diff = tr[0] - tr[1];
      long rango_min = min(rango.second - (inicio - rango.first), tr[2] - (inicio - tr[1]));
      buffer.push_back({ inicio + diff, rango_min });
      inicio = inicio + rango_min;
    }

    // Completamos el trozo del rango que falta, si es que falta:
    if ( inicio < (rango.first + rango.second) )
      buffer.push_back({ inicio, rango.second - (inicio - rango.first) });
  }
  
  return buffer;
}
