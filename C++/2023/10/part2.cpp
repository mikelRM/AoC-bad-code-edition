#include <iostream>
#include <fstream>
#include <ostream>
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
  ifstream archivo("part2.in");
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
 
  // Inicializamos el plano que guarda las posiciones del ciclo
  // inicialmente lleno de 0-s
  int y_max = plano.size();
  int x_max = plano.front().size();
  bool es_ciclo_p[x_max][y_max];
  for (int x = 0; x < x_max; x++)
    for (int y = 0; y < y_max; y++)
      es_ciclo_p[x][y] = false;


  // Ahora vamos recorriende el ciclo, en una única dirección, y lo
  // numeramos en orden (comenzando por el 10); esto es, el punto de
  // inicio lo ubicamos como 10, el siguiente 11, el siguiente 12,
  // etc.
  coord aux;
  coord camino = caminos[0];
  coord previo = inicio;
  int ii = 1;
  es_ciclo_p[inicio.first][inicio.second] = true;
  es_ciclo_p[camino.first][camino.second] = true;
  while (true) {
    ii++;
    aux = camino;
    camino = propagar_hacia_adelante(mirar(plano, camino), camino, previo);
    previo = aux;

    if ( camino == inicio ) {
      break;
    }
    es_ciclo_p[camino.first][camino.second] = true;
  }

  // Vamos recorriendo todo el mallado y determinando si estamos o no
  // en el área comprendida por el ciclo para contarlas.
  int suma = 0;
  for (int y = 0; y < y_max; y++) {
    int cruces_ciclo = 0;
    char orig_previo = 0;
    for (int x = 0; x < x_max; x++) {
      // Si estamos dentro del ciclo, sumamos un valor a la suma
      if (!es_ciclo_p[x][y]) {
	if (cruces_ciclo % 2 == 1)
	  suma++;
  	continue;
      }
      
      // Cuando nos encontramos una baldosa del ciclo:
      // No me apetece pensar más, y se que la 'S' en el mapa es un |
      if (plano[y][x] == '|' or plano[y][x] == 'S') {
	cruces_ciclo++;
	if (orig_previo) {
	  cout << endl << "ERROR en la linea " << y << "con previa " << orig_previo << ":" << endl;
	  for (int xx = 0; xx <= x; xx++)
	    if (es_ciclo_p[xx][y])
	      cout << plano[y][xx];
	    else cout << ".";
	  cout << endl;
	}
	continue;
      }

      if (plano[y][x] == '-')
	continue;

      if (orig_previo == 0) {
	orig_previo = plano[y][x];
	continue;
      }

      if ((plano[y][x] == '7' and orig_previo == 'L') or
	  (plano[y][x] == 'J' and orig_previo == 'F')) {
	cruces_ciclo++;
	orig_previo = 0;
      }

      if ((plano[y][x] == 'J' and orig_previo == 'L') or
	  (plano[y][x] == '7' and orig_previo == 'F')) {
	orig_previo = 0;
      }


    }
  }
  // |-  LJF7
  cout << "La respuesta a la parte 2 es: " << suma << "." << endl;
}
