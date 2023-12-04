#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
  map<int, map<string, int>> juegos;
  ifstream archivo;

  string linea, s_token, s_num;
  int juego, suma;
  int ix;
  
  archivo.open("part2.in");
  suma = 0;
  while( getline( archivo, linea )) {
    // Guardamos el juego
    ix = linea.find(":");
    juego =  stoi(linea.substr(ix-2, 2));
    linea = linea.substr(ix+1);

    // Inicializamos todo a cero
    juegos[juego]["red"] = 0;
    juegos[juego]["blue"] = 0;
    juegos[juego]["green"] = 0;

    // Rellenamos el mapa
    while (linea != "") {
      ix = min(linea.find(","), linea.find(";"));
      if ( ix > 0 ) {
	s_token = linea.substr(0, ix);
	linea = linea.substr(ix+1);
      } else {
	s_token = linea;
	linea = "";
      }

      ix = s_token.rfind(" ");
      s_num = s_token.substr(0, ix);
      s_token = s_token.substr(ix+1);

      juegos[juego][s_token] = max(stoi(s_num), juegos[juego][s_token]);
    }
    
    // Realmente no hacía falta rellenar todo el mapa, pero me apetecía.
    // Aquí vamos a comprobar si se cumplen lo necesario:
    suma = suma + juegos[juego]["red"] * juegos[juego]["blue"] * juegos[juego]["green"];

  }

  cout << "La respuesta a la parte 2 es: " << suma << endl;
  archivo.close();
    
}
