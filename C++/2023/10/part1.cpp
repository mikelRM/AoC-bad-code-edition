#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using coord=pair<int, int>;

coord mover(coord posicion, char direccion) {
  switch (direccion) {
  case 'N':
    return {posicion.first, posicion.second - 1};
  case 'S':
    return {posicion.first, posicion.second + 1};
  case 'E':
    return {posicion.first + 1, posicion.second};
  case 'O':
    return {posicion.first - 1, posicion.second};
  default:
    cout << "No se ha introducido una dirección válida" << endl;
    throw exception();
  }
}

char mirar(vector<vector<char>> const& mapa, coord const& pos) {
  return mapa[pos.second][pos.first];
}

coord propagar_hacia_adelante (char c, coord pos, coord prev) {
  switch (c) {
  case '|':
    if ( mover(pos, 'N') == prev )
      return mover(pos, 'S');
    return mover(pos, 'N');
  case '-':
    if ( mover(pos, 'E') == prev )
      return mover(pos, 'O');
    return mover(pos, 'E');
  case 'L':
    if ( mover(pos, 'N') == prev )
      return mover(pos, 'E');
    return mover(pos, 'N');
  case 'J':
    if ( mover(pos, 'N') == prev )
      return mover(pos, 'O');
    return mover(pos, 'N');
  case '7':
    if ( mover(pos, 'S') == prev )
      return mover(pos, 'O');
    return mover(pos, 'S');
  case 'F':
    if ( mover(pos, 'S') == prev )
      return mover(pos, 'E');
    return mover(pos, 'S');
  default:
    cout << "ERROR: Estamos atrapados" << endl;
    throw exception();
  }
}

int main()
{
  vector<vector<char>> plano;
  coord inicio;
  ifstream archivo("part1.in");
  string linea;

  // Leemos el archivo inicial
  int y = 0;
  while (getline(archivo, linea)) {
    plano.push_back({});
    int x = 0;
    for (char c : linea) {
      if (c == 'S') {
	inicio = {x, y};
      }
      plano.back().push_back(c);
      x++;
    }
    y++;
  }

  // Buscamos en las cuatro direcciones alrededor de 'S' los puntos
  // hacia los que siguen tuberías alineadas.
  vector<coord> caminos;
  if ((mirar(plano, mover(inicio, 'N')) == '|') or
      (mirar(plano, mover(inicio, 'N')) == '7') or
      (mirar(plano, mover(inicio, 'N')) == 'F'))
    caminos.push_back( mover(inicio, 'N') );

  if ((mirar(plano, mover(inicio, 'S')) == '|') or
      (mirar(plano, mover(inicio, 'S')) == 'J') or
      (mirar(plano, mover(inicio, 'S')) == 'L'))
    caminos.push_back( mover(inicio, 'S') );

  if ((mirar(plano, mover(inicio, 'E')) == '-') or
      (mirar(plano, mover(inicio, 'E')) == '7') or
      (mirar(plano, mover(inicio, 'E')) == 'J'))
    caminos.push_back( mover(inicio, 'E') );

  if ((mirar(plano, mover(inicio, 'O')) == '-') or
      (mirar(plano, mover(inicio, 'O')) == 'L') or
      (mirar(plano, mover(inicio, 'O')) == 'F'))
    caminos.push_back( mover(inicio, 'O') );

  // Comprobamos que sólo haya dos posibilidades
  if (caminos.size() != 2) {
    cout << "ERROR: Hemos encontrado más de dos caminos a seguir." << endl;
    throw exception();
  }

  // Si todo va bien, ya recorremos el ciclo sin problemas
  coord camino1 = caminos[0];
  coord camino2 = caminos[1];

  coord previo1 = inicio;
  coord previo2 = inicio;
  coord aux;

  int pasos = 1;
  while (true) {
    pasos++;
    aux = camino1;
    camino1 = propagar_hacia_adelante(mirar(plano, camino1), camino1, previo1);
    previo1 = aux;

    aux = camino2;
    camino2 = propagar_hacia_adelante(mirar(plano, camino2), camino2, previo2);
    previo2 = aux;
  
    if (camino1 == camino2) {
      cout << "La solución a la parte 1 es: " << pasos << endl;
      break;
    }
  }

  return 0;
}
