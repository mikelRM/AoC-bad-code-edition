#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int CONTADOR = 0;

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

  if (contador != 0)
    result.push_back(contador);

  return result;	
}


bool registros_numericos_iguales (vector<int> &v1, vector<int> &v2) {
  if (v1.size() != v2.size())
    return false;

  for (int i = 0; i < v1.size(); i++)
    if (v1[i] != v2[i])
      return false;
  
  return true;
}


// Cambiamos recursivamente las '?' y comprobamos al llegar al final si
// estamos ante una combinación adecuada.
void cambiar_siguiente_valor (string registro, vector<int> &numeros) {
  int i_tok = registro.find("?");

  if (i_tok == string::npos) {
    vector<int> aux = parse(registro);
    if (registros_numericos_iguales(numeros, aux))
      CONTADOR = CONTADOR + 1;
    return;
  }

  registro[i_tok] = '#';
  cambiar_siguiente_valor(registro, numeros);

  registro[i_tok] = '.';
  cambiar_siguiente_valor(registro, numeros);
}


int main()
{
  ifstream archivo("part1.in");
  string linea;
  int i_espacio, iii = 0;

  while (getline(archivo, linea)) {
    cout << "Leyendo línea: " << ++iii << endl;

    string reg_simb;
    vector<int> reg_num;
    i_espacio = linea.find(" ");
    reg_simb = linea.substr(0, i_espacio);
    linea = linea.substr(i_espacio + 1);
    while (linea != "") {
      i_espacio = linea.find(",");
      if (i_espacio != string::npos) {
	reg_num.push_back(stoi(linea.substr(0, i_espacio)));
	linea = linea.substr(i_espacio + 1);
      } else {
	reg_num.push_back(stoi(linea));
	linea = "";
      }
    }

    cambiar_siguiente_valor(reg_simb, reg_num);
  }
  
  cout << "El resultado de la parte 1 es: " << CONTADOR << endl;

}
