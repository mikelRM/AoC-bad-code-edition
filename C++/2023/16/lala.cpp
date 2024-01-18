#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> v = {1, 2, 3, 4};

  int& x = v.front();

  x = 10;

  for (int y : v)
    cout << y << ",";
  cout << endl;
}
