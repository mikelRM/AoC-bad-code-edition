#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main ()
{
  // Usar string::npos para comprobar si se ha encontrado algo o no
  ifstream archivo ("part1.in");
  string linea;

  while ( getline(archivo, linea) ) {
    cout << endl << linea << endl;
    
    size_t pos;
    string token;
    while ( (pos = linea.find_first_of("|: ")) != string::npos ) {
      token = linea.substr(0, pos);
      cout << token << endl;
      linea.erase(0, pos + 1);
    }
  }
    
}
