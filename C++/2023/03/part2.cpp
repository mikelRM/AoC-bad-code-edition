#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Numero {
  int linea;
  int columna;
  int numero;
  int digitos;
};

struct Engranaje {
  int linea;
  int columna;
  int n = 0;
  vector<int> numeros;
};

int main()
{
  const string s_numeros = "1234567890";
  vector<Numero> numeros;
  vector<Engranaje> engranajes;
  
  ifstream archivo("part2.in");
  string linea;
  int n_columnas, n_lineas, suma;

  n_lineas = 0;
  while (getline(archivo, linea)) {
    // BÚSQUEDA DE TODOS LOS ENGRANAJES
    int i = linea.find("*");
    int base = 0;
    while (i > 0) {
      Engranaje eng;
      eng.linea = n_lineas;
      eng.columna = base + i;
      engranajes.push_back(eng);
      base = base + i + 1;
      i = linea.substr(base).find("*");
    }
    
    // BÚSQUEDA DE TODOS LOS NÚMEROS
    base = 0;
    while (linea != "") {
      int i = linea.find_first_of(s_numeros);
      if (i < 0 or i > linea.length())
	break;

      int l = linea.substr(i).find_first_not_of(s_numeros);
      if (l < 0)
	l = linea.length() - i;

      Numero num;
      num.linea = n_lineas;
      num.columna = base + i;
      num.digitos = l;
      num.numero = stoi(linea.substr(i, l));
      numeros.push_back(num);
      
      linea = linea.substr(i + l);
      base = base + i + l;
    }
    
    n_lineas++;
  }
  n_columnas = linea.length();

  
  suma = 0;
  for (Engranaje &eng : engranajes) {
    for (Numero num : numeros) {
      if ( abs(num.linea - eng.linea) > 1 )
	continue;

      if ( (num.columna <= eng.columna + 1) and (num.columna + num.digitos >= eng.columna) ) {
	eng.n = eng.n + 1;
	eng.numeros.push_back(num.numero);
      }      
    }

    if ( eng.n == 2)
      suma += eng.numeros[0] * eng.numeros[1];
  }
  
  cout << "La respuesta a la parte 2 es: " << suma << endl;
}
