#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main ()
{
  ifstream archivo("part2.in");
  string linea;

  int i_dosp, i_barra;			// Índices
  int juego;				// Número de juego
  vector<int> v_ganadores, v_carton;	// Vectores

  map<int,vector<int>> m_ganadores, m_carton;
  map<int,int> m_num_cartones;
  
  while ( getline(archivo, linea) ) {
    v_ganadores.clear();
    v_carton.clear();
    
    // ÍNDICES DE LOS SEPARADORES
    i_dosp = linea.find(":");
    i_barra = linea.find("|");
    
    // PARSER DEL JUEGO
    string s_juego = linea.substr(0, i_dosp);
    int i_esp = s_juego.rfind(" ");
    juego = stoi(s_juego.substr(i_esp + 1));
    
    // PARSER DE NÚMEROS GANADORES
    string s_ganadores = linea.substr(i_dosp + 2, i_barra - i_dosp - 2);
    string token = "";
    while ( s_ganadores != "" ) {
      i_esp = s_ganadores.find(" ");
      if ( (token = s_ganadores.substr(0, i_esp)) != "")
	v_ganadores.push_back(stoi(token));
      s_ganadores = s_ganadores.substr(i_esp + 1);
    }

    // PARSER DE NÚMEROS DEL CARTÓN
    string s_carton = linea.substr(i_barra + 2);
    while ( s_carton != "" ) {
      i_esp = s_carton.find(" ");
      if ( i_esp == string::npos ) {
	v_carton.push_back(stoi(s_carton));
	s_carton = "";
      } else {
	if ( (token = s_carton.substr(0, i_esp)) != "")
	  v_carton.push_back(stoi(token));
	s_carton = s_carton.substr(i_esp + 1);
      }
    }

    m_ganadores.insert( {juego, v_ganadores} );
    m_carton.insert( {juego, v_carton} );
  }
  int numero_de_juegos = juego;

  for (int juego = 1; juego <= numero_de_juegos; juego++)
    m_num_cartones.insert( {juego, 1} );

  int suma = 0;
  for (int juego = 1; juego <= numero_de_juegos; juego++) {
    // Añadimos la cantidad de cartones al resultado
    suma = suma + m_num_cartones[juego];

    int subtotal = 0;
    for ( int num : m_ganadores[juego] ) {
      // Contamos cuantos cartones han sido premiados
      if ( find(m_carton[juego].begin(),
		m_carton[juego].end(),
		num) != m_carton[juego].end() )
	subtotal++;
    }

    // Sumamos los cartones premiados
    if (subtotal == 0)
      continue;

    for (int j = 1; j <= subtotal; j++) {
      if ( juego + j > numero_de_juegos )
	continue;
      m_num_cartones[juego+j] += m_num_cartones[juego];
    }
  }

  cout << "El resultado de la parte 2 es: " << suma << endl;
  
}
