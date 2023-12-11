#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<long, pair<long,long>> get_seeds (string line);

int main ()
{
  ifstream archivo ("part1.in");
  string linea;

  // Mapa de <semillas, <intermedio, final>>
  map<long, pair<long,long>> sem_a_loc;
  
  while ( getline(archivo, linea) ) {
    if ( linea == "") {
      for (auto& x : sem_a_loc)
	x.second.first = x.second.second;
      continue;
    }

    if ( linea.find("seeds:") != string::npos ) {
      sem_a_loc = get_seeds(linea);
      continue;
    }

    if ( linea.find("map:") != string::npos ) {
      continue;
    }

    // Si no se cumplen ninguna de las opciones anteriores, entonces
    // estamos en la definición de los rangos
    int i_esp = linea.find(" ");
    long dest_start = stol(linea.substr(0, i_esp));
    linea = linea.substr(i_esp + 1);
    
    i_esp = linea.find(" ");
    long orig_start = stol(linea.substr(0, i_esp));
    linea = linea.substr(i_esp + 1);
    
    long rango = stol(linea);
    
    // Hacemos los cambios pertinentes
    for (auto& x : sem_a_loc) {
      if ( (x.second.first >= orig_start) and
	   (x.second.first < orig_start + rango) )
	x.second.second = x.second.first + (dest_start - orig_start);
    }
  }
  
  long min_loc = 1000000000;
  for (auto const& x : sem_a_loc)
    min_loc = (x.second.second < min_loc) ? x.second.second : min_loc;

  cout << "La respuesta a la parte 1 es: " << min_loc << endl;
}


map<long, pair<long,long>> get_seeds (string line)
{
  map<long, pair<long,long>> mapa;
  int i_find;
  string token;

  i_find = line.find(":");
  line = line.substr(i_find + 1);
  while ( line != "") {
    i_find = line.find(" ");
    token = line.substr(0, i_find);
    line = line.substr(i_find + 1);

    if ( i_find == string::npos ) {
      token = line;
      line = "";
    }    
    
    if ( (token == "") or (token == " ") )
      continue;

    mapa.insert( {stol(token), make_pair(stol(token), stol(token))} );
  }

  return mapa;
}
