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

long calcular_peso (vector<string>& mapa)
{
  long peso_total = 0;
  for (int j = 0; j < mapa.front().size(); ++j) {
    for (int i = 0; i < mapa.size(); ++i) {
      if (mapa[i][j] == 'O') {
	peso_total = peso_total + (mapa.size() - i);
      }
    }
  }

  return peso_total;
}

int main()
{
  ifstream archivo("input.in");
  string linea;

  vector<string> mapa_piedras;
  while (getline(archivo, linea)) {
    mapa_piedras.push_back(linea);
  }

  vector<vector<string>> lista_previos_mapa_piedras = {mapa_piedras};
  bool salir_del_ciclo = false;
  int inicio_ciclo, longitud_ciclo;
  for (int contador = 1; contador < 1000000000; ++contador) {
    rotar_un_ciclo(mapa_piedras);
    for (int j = 0; j < lista_previos_mapa_piedras.size(); ++j) {
      if (lista_previos_mapa_piedras[j] == mapa_piedras) {
	inicio_ciclo = j;
	longitud_ciclo = contador - j;
	salir_del_ciclo = true;
	break;
      }
    }

    if (salir_del_ciclo)
      break;

    lista_previos_mapa_piedras.push_back(mapa_piedras);
  }
  
  long modulo_ciclo = (1000000000 - inicio_ciclo) % longitud_ciclo;
  long resultado = calcular_peso(lista_previos_mapa_piedras[inicio_ciclo + modulo_ciclo]);
  cout << "El resultado de la parte 2 es: " << resultado << endl;


  // cout << endl;
  // for (vector<string>& mapas : lista_previos_mapa_piedras)
  //   cout << calcular_peso(mapas) << endl;
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
