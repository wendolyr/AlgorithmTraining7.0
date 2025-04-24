#include <iostream>

using namespace std;

int main() {
  int x1 = 0, y1 = 0;
  cin >> x1 >> y1;

  cout << (x1 ^ y1) << endl;
  int x2 = 0, c = 0;
  cin >> x2 >> c;

  cout << (x2 ^ c);

  return 0;
}