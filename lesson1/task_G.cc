#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n = 0, k = 0;
  cin >> n >> k;

  vector<pair<int, int>> blocks(n + 1);
  int max_len = 0;
  for (int i = 1; i <= n; i++) {
    cin >> blocks[i].first >> blocks[i].second;
    if (blocks[i].second == 1) {
      max_len += blocks[i].first;
    }
  }

  vector<vector<int>> result(k + 1, vector<int>(max_len + 1));
  for (int color = 1; color <= k; color++) {
    for (int len = 1; len <= max_len; len++) {
      result[color][len] = -1;
    }
    result[color][0] = 0;
  }

  for (int i = 1; i <= n; i++) {
    int len = blocks[i].first, color = blocks[i].second;
    for (int j = max_len; j >= 0; j--) {
      if (result[color][j] != -1 && j + len <= max_len &&
          result[color][j + len] == -1) {
        result[color][j + len] = i;
      }
    }
  }

  bool find = false;
  for (int i = 1; i < max_len;
       i++) {  // не включительно (макс и так по условию можно построить)
    bool flag = true;
    for (int j = 1; j <= k; j++) {
      if (result[j][i] == -1) {
        flag = false;
      }
    }

    if (!find && flag) {
      find = true;
    }

    if (flag) {
      cout << "YES" << endl;
      for (int q = 1; q <= k; q++) {
        int current_len = i;
        while (current_len != 0) {
          cout << result[q][current_len] << ' ';
          current_len -= blocks[result[q][current_len]].first;
        }
      }
      break;
    }
  }

  if (!find) {
    cout << "NO" << endl;
  }

  return 0;
}