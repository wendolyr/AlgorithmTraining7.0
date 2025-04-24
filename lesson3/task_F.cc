#include <iostream>
#include <vector>

using namespace std;

void set_bit(int x, int y, int z, vector<vector<vector<unsigned int>>> &board) {
  int num_int = z >> 5;
  int num_bit = z % 32;

  board[x][y][num_int] |= (1 << num_bit);
}

int get_bit(int x, int y, int z,
            const vector<vector<vector<unsigned int>>> &board) {
  int num_int = z >> 5;
  int num_bit = z % 32;

  return board[x][y][num_int] & (1 << num_bit) ? 1 : 0;
}

int main() {
  int n = 0, k = 0;
  cin >> n >> k;

  int size = (n + 31) >> 5;
  vector<vector<vector<unsigned int>>> board(
      n, vector<vector<unsigned int>>(n, vector<unsigned int>(size, 0)));

  for (int i = 0; i < k; i++) {
    int x = 0, y = 0, z = 0;
    cin >> x >> y >> z;
    x--;
    y--;
    z--;

    for (int j = 0; j < n; j++) {
      for (int q = 0; q < n; q++) {
        set_bit(x, j, q, board);
        set_bit(j, y, q, board);
        set_bit(j, q, z, board);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int q = 0; q < n; q++) {
        if (!get_bit(i, j, q, board)) {
          cout << "NO" << endl;
          cout << i + 1 << ' ' << j + 1 << ' ' << q + 1;
          return 0;
        }
      }
    }
  }

  cout << "YES";

  return 0;
}