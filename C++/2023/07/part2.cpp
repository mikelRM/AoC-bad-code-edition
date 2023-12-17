#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const string orden_cartas = "AKQT98765432J";
enum JUGADAS {POKER, CUARTETO, FULL, TRIO, DOBLES, PAREJA, NADA};

class Mano {
public:
  Mano(string cartas, string apuesta);
  void print();
  int apuesta;
  string cartas;
  map<char,int> ocr_carta;
  JUGADAS juego;
};


int main()
{
  ifstream archivo;
  string linea;
  int i_esp;
  vector<Mano> manos_jugadas;
    
  archivo.open("part2.in");
  while ( getline(archivo, linea) ) {
    i_esp = linea.find(" ");
    manos_jugadas.push_back(Mano(linea.substr(0, i_esp), linea.substr(i_esp + 1)));
  }

  sort(manos_jugadas.begin(), manos_jugadas.end(),
       [](auto& left, auto& right)
       {
	 // Primero: por jugada
	 if (left.juego != right.juego)
	   return left.juego < right.juego;
	 
	 // Despues por el valor de las cartas:
	 for (int ii = 0; ii < 5; ++ii)
	   if (left.cartas[ii] != right.cartas[ii])
	     return orden_cartas.find(left.cartas[ii]) < orden_cartas.find(right.cartas[ii]);

	 // Si no, son la misma jugada
	 cout << "Estamos ante la misma jugada" << endl;
	 return true;
       });

  long long suma = 0;
  for (int ii = 0; ii < manos_jugadas.size(); ++ii)
    suma += manos_jugadas[ii].apuesta * (manos_jugadas.size() - ii);

  cout << "La respuesta a la parte 2 es: " << suma << endl;
}


Mano::Mano(string cartas, string apuesta) {
  this->cartas = cartas;
  this->apuesta = stoi(apuesta);

  for (char c : this->cartas) {
    this->ocr_carta[c] += 1;
  }

  // ASOCIAMOS TODOS LOS JOQUERS A LOS QUE MÁS HAYA
  // Búsqueda del máximo
  char fmax;
  int smax = 0;
  for (auto const& entry : this->ocr_carta) {
    if ( (entry.first == 'J') or (smax > entry.second) )
      continue;
    fmax = entry.first;
    smax = entry.second;
  }

  // Asociación al máximo y la posterior eliminación de la J
  this->ocr_carta[fmax] += this->ocr_carta['J'];
  this->ocr_carta.erase('J');
  
  // DECIDIMOS QUÉ HACEMOS CON TODO ESTO
  switch (this->ocr_carta.size()) {
  case 0:			// Sólo puede ser si la mano son 'JJJJJ'
    cout << "POKER DE J: " << this->cartas << endl;
    this->juego = POKER;
    break;
  case 1:
    this->juego = POKER;
    break;
  case 2:
    this->juego = FULL;
    for (auto const& it : this->ocr_carta)
      if (it.second == 4)
	this->juego = CUARTETO;
    break;
  case 3:
    this->juego = DOBLES;
    for (auto &it : this->ocr_carta)
      if (it.second == 3)
	this->juego = TRIO;
    break;
  case 4:
    this->juego = PAREJA;
    break;
  case 5:
    this->juego = NADA;
    break;
  default:
    cout << "ERROR EN LA DECISIÓN DE LAS JUGADAS." << endl;
    cout << this->ocr_carta.size() << endl;
  }
}
