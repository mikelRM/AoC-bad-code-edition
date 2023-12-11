#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<long> leer_semillas (string linea);

class MapaRango {
public:
  vector<long> destino,		// Número base en destino
    origen,			// Número base en origen
    rango; 			// Longitud del rango
  string nombre;
  MapaRango(string nombre);
  void leer_linea(string linea);
  long forward (long num);
  long backward (long num);
};

int main()
{
  ifstream archivo;
  string linea;
  vector<MapaRango> mapas;
  vector<long> semillas;

  archivo.open("part2.in");
  while ( getline(archivo, linea) ) {
    // Pasamos de las líneas vacías
    if ( linea == "")
      continue;

    // Leemos la línea con las semillas
    if ( linea.find("seeds:") != string::npos ) {
      semillas = leer_semillas(linea);
      continue;
    }

    // Vamos llenando los mapas en el orden indicado. Esta solución se
    // basa en que todos los mapas se dan en orden; esto es:
    //     map_ab, map_bc, map_cd, map_de, etc.
    if ( linea.find("map:") != string::npos ) {
      int i_esp = linea.find(" ");
      mapas.push_back(MapaRango(linea.substr(0, i_esp)));
      continue;
    }

    // Añadimos los rangos a la lista de rangos del mapa
    int i_esp = linea.find(" ");
    mapas.back().destino.push_back(stol(linea.substr(0, i_esp)));

    linea = linea.substr(i_esp + 1);
    i_esp = linea.find(" ");
    mapas.back().origen.push_back(stol(linea.substr(0, i_esp)));

    linea = linea.substr(i_esp + 1);
    mapas.back().rango.push_back(stol(linea));
  }
  archivo.close();

  // for (MapaRango const& mapa: mapas) {
  //   cout << endl << mapa.nombre << endl;
  //   cout << "Size of array: " << mapa.rango.size() << endl;
  // }

  // EL ARCHIVO YA ESTÁ LEÍDO. YA "SOLO" FALTA LA LÓGICA.
}


vector<long> leer_semillas (string linea) {
  vector<long> semillas;
  int ii;
  string token;

  ii = linea.find(":");
  linea = linea.substr(ii + 1);
  while ( linea != "") {
    ii = linea.find(" ");
    token = linea.substr(0, ii);
    linea = linea.substr(ii + 1);

    if ( ii == string::npos ) {
      token = linea;
      linea = "";
    }    
    
    if ( (token == "") or (token == " ") )
      continue;

    semillas.push_back(stol(token));
  }

  return semillas;
  
}


MapaRango::MapaRango (string nombre) {
  this->nombre = nombre;
}

void MapaRango::leer_linea(string linea) {
  cout << "Estamos dentro de un mapa." << endl;
}
