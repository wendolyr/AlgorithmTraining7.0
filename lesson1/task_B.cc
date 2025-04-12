#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t = 0;
  cin >> t;
  vector<vector<int>> massives;
  for (int i = 0; i < t; i++) {
    vector<int> temp;
    int n = 0;
    cin >> n;
    for (int j = 0; j < n; j++) {
      int a = 0;
      cin >> a;
      temp.push_back(a);
    }
    massives.push_back(temp);
  }

  for (int i = 0; i < t; i++) {
    vector<int> result;
    int counter = 0;
    int len = 0;
    int min = massives[i][0];
    for (size_t j = 0; j < massives[i].size(); j++) {
      if (massives[i][j] < min) {
        min = massives[i][j];
      }
      len++;
      if (min >= len && j == massives[i].size() - 1) {
        counter++;
        result.push_back(len);
      } else if (min < len && j != massives[i].size() - 1) {
        counter++;
        result.push_back(len - 1);
        len = 1;
        min = massives[i][j];
      } else if (min < len && j == massives[i].size() - 1) {
        counter++;
        result.push_back(len - 1);
        len = 1;
        counter++;
        result.push_back(len);
      }
    }

    cout << counter << endl;
    for (auto x : result) {
      cout << x << ' ';
    }
    cout << endl;
  }

  return 0;
}