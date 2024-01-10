#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

map<pair<string, vector<int>>,long> mapa_cache;

long contar(string sims, vector<int> nums,
	    map<pair<string, vector<int>>,long>& dp)
{
  // Cuando ya no tenemos números en la lista
  if (nums.size() == 0) {
    if (sims.find("#") == string::npos)
      return dp[{sims, nums}] = 1;
    else
      return dp[{sims, nums}] = 0;
  }

  // Si la suma de los números es mayor al tamaño de la cadena:
  if (accumulate(nums.begin(), nums.end(), nums.size() - 1) > sims.size())
    return dp[{sims, nums}] = 0;

  // Si ya tenemos el caso guardado:
  if (dp.find({sims, nums}) != dp.end())
    return dp[{sims, nums}];

  // De lo cotrario, pasamos al ataque. Para no alargar mucho el
  // código, vamos caracter a caracter:
  if (sims[0] == '.')
    return dp[{sims,nums}] = contar(sims.substr(1), nums, dp);
  
  if (sims[0] == '?')
    return dp[{sims,nums}] = contar(sims.substr(1), nums, dp)
      + contar('#' + sims.substr(1), nums, dp);
  
  if (sims[0] == '#') {
    int i_punto = sims.find(".");

    // TODO: Ir reduciendo el tamaño de la cadena...
  }
}
int main()
{
  ifstream archivo("part2.in");
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
    
    
  }
  


}

/*
 NOTAS:

 La primera vez que miramos una clave en un diccionario, si dicha
 clave no está en el diccionario, crea la entrada; por lo que para
 comprobar si el caso correspondiente se ha calculado ya utilizar:

 if (dp.find(key) == dp.end()) --> quiere decir que no existe.
*/
