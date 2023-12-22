#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parse (string registro) {
  vector<int> result;

  int contador = 0;
  for (char c : registro) {
    if (c == '#')
      contador++;
    else if (c == '.') {
      if (contador)
	result.push_back(contador);
      contador = 0;
    }
    else
      cout << "No entiendo el siguiente caracter: " << c << endl;
  }

  return result;	
}

int main()
{
  ifstream archivo("part1.in");
  string linea;
  
  while (getline(archivo, linea)) {
    cout << linea << endl;
  }

  string prueba = "##.....#.#.####...#.";
  cout << endl << prueba << endl;
  for (int x : parse(prueba))
    cout << x << " ";
  cout << endl;
  
}
