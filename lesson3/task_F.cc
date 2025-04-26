#include <iostream>
#include <vector>

using namespace std;

void set_bit(int a, int b, vector<vector<unsigned long long>>& board) {
  int num_int = b >> 6;
  int num_bit = b & 63;

  board[a][num_int] |= (1ULL << num_bit);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 0, k = 0;
  cin >> n >> k;

  int size = (n + 63) >> 6;
  vector<vector<unsigned long long>> yz(n, vector<unsigned long long>(size, 0)),
      xz(n, vector<unsigned long long>(size, 0)),
      xy(n, vector<unsigned long long>(size, 0));

  for (int i = 0; i < k; i++) {
    int x = 0, y = 0, z = 0;
    cin >> x >> y >> z;
    x--;
    y--;
    z--;

    set_bit(y, z, yz);
    set_bit(z, x, xz);
    set_bit(y, x, xy);
  }

  if (k == 0) {
    cout << "NO" << endl << "1 1 1" << endl;
    return 0;
  }

  for (int y = 0; y < n; ++y) {
    for (int wz = 0; wz < size; ++wz) {
      unsigned long long freeZ = ~yz[y][wz];
      while (freeZ) {
        int counter = 0;
        unsigned long long temp = freeZ;
        while ((temp & 1) == 0) {
          temp >>= 1;
          counter++;
        }
        int z = (wz << 6) + counter;
        if (z >= n) break;

        for (int wx = 0; wx < size; ++wx) {
          unsigned long long freeX = ~(xz[z][wx]) & ~(xy[y][wx]);
          if (freeX) {
            counter = 0;
            temp = freeX;
            while ((temp & 1) == 0) {
              temp >>= 1;
              counter++;
            }
            int x = (wx << 6) + counter;
            if (x >= n) continue;
            cout << "NO" << endl
                 << x + 1 << ' ' << y + 1 << ' ' << z + 1 << endl;
            return 0;
          }
        }
        freeZ &= freeZ - 1;
      }
    }
  }

  cout << "YES" << endl;

  return 0;
}