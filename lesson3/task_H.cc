#include <iostream>

using namespace std;

class Fenwick3D {};

int main() {
  int n = 0;
  cin >> n;

  Fenwick3D t(n);
  int command = 0;

  while (command != 3) {
    cin >> command;
    if (command == 1) {
      int x = 0, y = 0, z = 0, k = 0;
      cin >> x >> y >> z >> k;
      t.update(x, y, z, k);
    } else if (command == 2) {
      int x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        }
  }
}