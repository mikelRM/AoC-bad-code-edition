#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Luz {int i; int j; char direccion;};

void propagar_en_vacio (Luz* haz) {
  switch (haz->direccion) {
  case '>': haz->j++; break;
  case '<': haz->j--; break;
  case '^': haz->i--; break;
  case 'v': haz->i++; break;
  default: cout << "ERROR al propagar..."; break;
  }
}

void reflejar_en_espejo (char espejo, Luz* haz) {
  switch (haz->direccion) {
  case '>': 
    if (espejo == '/')  haz->direccion = '^';
    if (espejo == '\\') haz->direccion = 'v';
    break;
  case '<':
    if (espejo == '/')  haz->direccion = 'v';
    if (espejo == '\\') haz->direccion = '^';
    break;
  case '^':
    if (espejo == '/')  haz->direccion = '>';
    if (espejo == '\\') haz->direccion = '<';
    break;
  case 'v':
    if (espejo == '/')  haz->direccion = '<';
    if (espejo == '\\') haz->direccion = '>';
    break;
  default:
    cout << "ERROR al 'reflejar_en_espejo'..." << endl; break;
  }
}

bool haz_choca_con_pared (Luz const* haz, int const& n_filas, int const& n_columnas) {
  if ((haz->direccion == '<' and haz->j == 0) or
      (haz->direccion == '>' and haz->j == n_columnas - 1) or
      (haz->direccion == 'v' and haz->i == n_filas - 1) or
      (haz->direccion == '^' and haz->i == 0))
    return true;
  return false;
}

int main()
{
  ifstream archivo("input.in");
  string linea;

  vector<string> mapa_espejos; 
  while (getline(archivo, linea)) {
    mapa_espejos.push_back(linea);
  }

  int n_filas = mapa_espejos.size();
  int n_columnas = mapa_espejos.front().size();

  vector<Luz> frentes = {{0, 0, '>'}};
  vector<vector<vector<char>>> historico(n_filas, vector<vector<char>>(n_columnas, {'.'}));
  while (frentes.size() > 0) {
    Luz* frente = &frentes.front();
    while (true) {
      char sitio = mapa_espejos[frente->i][frente->j];
      vector<char>& hist = historico[frente->i][frente->j];
      if (find(hist.begin(), hist.end(), frente->direccion) != hist.end())
	break;

      hist.push_back(frente->direccion);
	
      if (sitio == '/' or sitio == '\\') {
	reflejar_en_espejo(sitio, frente);
      }

      if (sitio == '-' and ((frente->direccion == 'v') or
			    (frente->direccion == '^'))) {
	frentes.push_back({frente->i, frente->j, '>'});
	frente = &frentes.front();
	frente->direccion = '<';
      }
	
      if (sitio == '|' and ((frente->direccion == '<') or
			    (frente->direccion == '>'))) {
	frentes.push_back({frente->i, frente->j, 'v'});
	frente = &frentes.front();
	frente->direccion = '^';
      }

      if (haz_choca_con_pared(frente, n_filas, n_columnas)) {
	break;
      }

      propagar_en_vacio(frente);
    }

    frentes.erase(frentes.begin());
  }

  long suma = 0;
  for (int i = 0; i < n_filas; ++i) 
    for (int j = 0; j < n_columnas; ++j) 
      if (historico[i][j].size() > 1)
	suma++;


  cout << "La respuesta a la parte 1 es: " << suma << endl;
  
}

