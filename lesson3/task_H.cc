#include <iostream>
#include <vector>

using namespace std;

class Fenwick3D {
 private:
  vector<vector<vector<long long>>> data;
  int size;

 public:
  Fenwick3D(int n)
      : data(n, vector<vector<long long>>(n, vector<long long>(n, 0))),
        size(n) {}

  void update(int x, int y, int z, long long value) {
    for (int i = x; i < size; i |= (i + 1)) {
      for (int j = y; j < size; j |= (j + 1)) {
        for (int k = z; k < size; k |= (k + 1)) {
          data[i][j][k] += value;
        }
      }
    }
  }

  long long sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) +
           sum(x1 - 1, y1 - 1, z2) - sum(x2, y2, z1 - 1) +
           sum(x1 - 1, y2, z1 - 1) + sum(x2, y1 - 1, z1 - 1) -
           sum(x1 - 1, y1 - 1, z1 - 1);
  }

  long long sum(int x, int y, int z) {
    long long sum = 0;

    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
          sum += data[i][j][k];
        }
      }
    }
    return sum;
  }
};

int main() {
  int n = 0;
  cin >> n;

  Fenwick3D t(n);
  vector<vector<vector<long long>>> a(
      n, vector<vector<long long>>(n, vector<long long>(n, 0)));
  int command = 0;

  while (command != 3) {
    cin >> command;
    if (command == 1) {
      int x = 0, y = 0, z = 0;
      long long k = 0;
      cin >> x >> y >> z >> k;
      a[x][y][z] += k;
      t.update(x, y, z, k);
    } else if (command == 2) {
      int x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      cout << t.sum(x1, y1, z1, x2, y2, z2) << endl;
    }
  }
}