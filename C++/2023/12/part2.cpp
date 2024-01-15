#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

map<pair<string, vector<int>>, long long> mapa_cache;

long long contar(string sims, vector<int> nums,
	    map<pair<string, vector<int>>, long long>& dp)
{
  if (nums.size() == 0) {
    if (sims.find("#") == string::npos)
      return dp[{sims, nums}] = 1;
    else
      return dp[{sims, nums}] = 0;
  }

  if (accumulate(nums.begin(), nums.end(), nums.size() - 1) > sims.size())
    return dp[{sims, nums}] = 0;

  if (dp.find({sims, nums}) != dp.end())
    return dp[{sims, nums}];

  if (sims[0] == '.')
    return dp[{sims,nums}] = contar(sims.substr(1), nums, dp);
  
  if (sims[0] == '?')
    return dp[{sims,nums}] = contar(sims.substr(1), nums, dp)
      + contar('#' + sims.substr(1), nums, dp);
  
  if (sims[0] == '#') {
    int i_punto = sims.find(".");
    if (sims[nums[0]] == '#' || i_punto < nums[0] && i_punto != string::npos)
      return dp[{sims, nums}] = 0;
    
    else if (sims[nums[0]] == '?' || sims[nums[0]] == '.') 
      return dp[{sims, nums}] = contar(sims.substr(nums[0] + 1),
				       vector<int>(nums.begin() + 1, nums.end()),
				       dp);
  }

  cout << "Hemos llegado al final de la función sin éxito?" << endl;
  exit(1);
  return 0;
}

int main()
{
  ifstream archivo("part2.in");
  string linea;
  int i_espacio;
  long long suma = 0;
  
  while (getline(archivo, linea)) {
    string simbs;
    vector<int> nums;

    i_espacio = linea.find(" ");
    simbs = linea.substr(0, i_espacio);
    linea = linea.substr(i_espacio + 1);

    simbs = simbs + "?" + simbs + "?" + simbs + "?" + simbs + "?" + simbs + "..";
    linea = linea + "," + linea + "," + linea + "," + linea + "," + linea;
    while (linea != "") {
      i_espacio = linea.find(",");
      if (i_espacio != string::npos) {
	nums.push_back(stoi(linea.substr(0, i_espacio)));
	linea = linea.substr(i_espacio + 1);
      } else {
	nums.push_back(stoi(linea));
	linea = "";
      }
    }

    suma = suma + contar(simbs, nums, mapa_cache);
  }
  
  cout << "El resultado de la parte 2 es: " << suma << endl;
}
