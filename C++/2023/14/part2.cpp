#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void inclinar_hacia_el_norte (vector<string>& mapa);
void inclinar_hacia_el_sur (vector<string>& mapa);
void inclinar_hacia_el_este (vector<string>& mapa);
void inclinar_hacia_el_oeste (vector<string>& mapa);

void rotar_un_ciclo (vector<string>& mapa)
{
  inclinar_hacia_el_norte(mapa);
  inclinar_hacia_el_oeste(mapa);
  inclinar_hacia_el_sur(mapa);
  inclinar_hacia_el_este(mapa);
}

int main()
{
  ifstream archivo("test.in");
  string linea;

  vector<string> mapa_piedras;
  
  while (getline(archivo, linea)) {
    mapa_piedras.push_back(linea);
  }

  // Los resultados se van repitiendo en ciclos.  Hay que buscar el
  // tamaño del ciclo y ver en qué punto queda el 1000000000 de la
  // repetición para seleccionar el mapa correspodiente.  Finalmente,
  // se calcula el peso hacia el norte.
  vector<string> mapa_piedras_buffer;
  for (int contador = 0; contador < 1000000000; ++contador) {
    mapa_piedras_buffer = mapa_piedras;
    rotar_un_ciclo(mapa_piedras);

    if (mapa_piedras == mapa_piedras_buffer)
      break;
    else if (contador % 10000 == 0)
      cout << "Ciclo: " << contador << endl;

  }
  
  
  //cout << "El resultado de la parte 2 es: " << peso_total << endl;
}


void inclinar_hacia_el_norte (vector<string>& mapa)
{
   for (int j = 0; j < mapa.front().size(); ++j) {
    int i_obstaculo = -1;
    for (int i = 0; i < mapa.size(); ++i) {
      if (mapa[i][j] == '#')
	i_obstaculo = i;
      if (mapa[i][j] == 'O') {
	mapa[i][j] = '.';
	mapa[i_obstaculo+1][j] = 'O';
	i_obstaculo = i_obstaculo + 1;
      }
    }
  }
}

void inclinar_hacia_el_sur (vector<string>& mapa)
{
  for (int j = 0; j < mapa.front().size(); ++j) {
    int i_obstaculo = mapa.size();
    for (int i = mapa.size() - 1; i >= 0; --i) {
      if (mapa[i][j] == '#')
	i_obstaculo = i;
      if (mapa[i][j] == 'O') {
	mapa[i][j] = '.';
	mapa[i_obstaculo-1][j] = 'O';
	i_obstaculo = i_obstaculo - 1;
      }
    }
  }
}


void inclinar_hacia_el_oeste (vector<string>& mapa)
{
  for (string& s : mapa) {
    int i_obstaculo = -1;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '#')
	i_obstaculo = i;
      if (s[i] == 'O') {
	s[i] = '.';
	s[i_obstaculo+1] = 'O';
	i_obstaculo = i_obstaculo + 1;
      }
    }
  }
}

void inclinar_hacia_el_este (vector<string>& mapa)
{
  for (string& s : mapa) {
    int i_obstaculo = s.size();
    for (int i = s.size() - 1; i >= 0; --i) {
      if (s[i] == '#')
	i_obstaculo = i;
      if (s[i] == 'O') {
	s[i] = '.';
	s[i_obstaculo-1] = 'O';
	i_obstaculo = i_obstaculo - 1;
      }
    }
  }
}


