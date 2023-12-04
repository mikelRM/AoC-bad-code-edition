#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  const string numeros[9] =
    {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  ifstream archivo ("part2.in");
  char c;
  string linea, primero, ultimo;
  int suma;
  bool primero_vacio;

  suma = 0;
  while (getline(archivo, linea)) {
    primero_vacio = true;
    for (int i = 0; i < linea.length(); i++) {

      // Comprobación de que sea dígito
      c = linea[i];
      if ( isdigit(c) ) {
	if ( primero_vacio ) {
	  primero = c;
	  primero_vacio = false;
	}
	ultimo = c;
	continue;
      }

      // Comprobación de texto
      for (int j=0; j < 9; j++) {
	string numero = numeros[j];
	if (numero.length() > linea.length() - i) continue;

	if ( numero == linea.substr(i, numero.length()) ) {
	  if ( primero_vacio ) {
	    primero = to_string(j + 1);
	    primero_vacio = false;
	  }
	  ultimo = to_string(j + 1);
	}
      }
    }
    suma = suma + stoi(primero + ultimo);
  }

  cout << "La respuesta de la parte 2: " << suma << endl;
  archivo.close();
}
