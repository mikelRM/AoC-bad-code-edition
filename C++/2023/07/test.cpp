#include <iostream>
#include <map>

using namespace std;

int main ()
{
  map<char,int> ocurrencia;

  ocurrencia['a'] += 1;
  ocurrencia['a'] += 1;
  ocurrencia['c'] += 1;
  ocurrencia['a'] += 1;
  ocurrencia['a'] += 1;
  ocurrencia['a'] += 1;

  for ( auto x : ocurrencia )
    cout << x.first << " " << x.second << endl;
    
}
