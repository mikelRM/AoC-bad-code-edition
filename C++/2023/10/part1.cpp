#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct Punto {
  int x;
  int y;
  auto operator<=> (const Punto &) const = default;
  Punto operator+ (const Punto &other) {
    return Punto{x + other.x, y + other.y};
  }
};

class Tuberia {
public:
  char tipo;
  Punto pos;
  Tuberia (char tipo, Punto pos) { this->tipo = tipo; this->pos = pos;}
};

int main()
{
  map<Punto, Tuberia> plano;
  Punto inicio;
  
  ifstream archivo("part1.in");
  string linea;

  // Leemos el archivo inicial
  int y = 0;
  while (getline(archivo, linea)) {
    int x = 0;
    for (char c : linea) {
      if (c == 'S') {
	inicio = {x, y};
	cout << "Hemos encontrado el monstruo en: " << x << ", " << y << endl;
      }
      plano.insert({ {x, y} , Tuberia(c, {x, y}) });
      x++;
    }
    y++;
  }

  // Detectamos hacia dónde podemos ir
  
}
