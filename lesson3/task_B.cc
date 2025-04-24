#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n = 0;
  cin >> n;
  vector<vector<int>> m(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> m[i][j];
    }
  }

  vector<int> result(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        result[i] |= m[i][j];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << result[i] << ' ';
  }

  return 0;
}