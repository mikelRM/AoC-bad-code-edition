#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main ()
{
  ifstream archivo("part1.in");
  string linea;

  int i_dosp, i_barra;			// Índices
  int juego;				// Número de juego
  vector<int> v_ganadores, v_carton;	// Vectores

  int suma = 0;
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

    int subtotal = 0;
    for ( int num : v_ganadores ) {
      if ( find(v_carton.begin(), v_carton.end(), num) != v_carton.end() )
	subtotal = (subtotal > 0) ? subtotal * 2 : 1;
    }

    suma = suma + subtotal;
  }

  cout << "La respuesta de la parte 1 es: " << suma << endl;
}
