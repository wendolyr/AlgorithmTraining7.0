#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n = 0, m = 0;
  cin >> n >> m;
  if (n >= 1 && m >= 1) {
    vector<pair<int, int>> groups;
    vector<pair<int, int>> classrooms;

    for (int i = 0; i < n; i++) {
      pair<int, int> temp;
      temp.first = i + 1;
      cin >> temp.second;
      groups.push_back(temp);
    }

    for (int i = 0; i < m; i++) {
      pair<int, int> temp;
      temp.first = i + 1;
      cin >> temp.second;
      classrooms.push_back(temp);
    }

    sort(groups.begin(), groups.end(),
         [](auto a, auto b) { return a.second < b.second; });
    sort(classrooms.begin(), classrooms.end(),
         [](auto a, auto b) { return a.second < b.second; });

    vector<int> result(n + 1, 0);

    int count = 0;
    int j = 0;
    for (int i = 0; i < n && j < m; ++i) {
      while (j < m && classrooms[j].second < groups[i].second + 1) {
        j++;
      }
      if (j < m) {
        result[groups[i].first] = classrooms[j].first;
        count++;
        j++;
      }
    }

    cout << count << endl;
    for (int i = 1; i <= n; ++i) {
      if (i != n) {
        cout << result[i] << " ";
      } else {
        cout << result[i];
      }
    }
  } else {
    std::cout << "ERROR" << std::endl;
  }

  return 0;
}