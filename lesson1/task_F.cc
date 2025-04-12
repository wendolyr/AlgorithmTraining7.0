#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int num_bars = 0, weight = 0;
  cin >> num_bars >> weight;

  if (num_bars < 1 || weight < 1) {
    cout << "ERROR" << endl;
    return 1;
  }

  int *things = new int[num_bars]();
  for (int i = 0; i < num_bars; i++) {
    cin >> things[i];
  }

  int *cost = new int[num_bars]();
  for (int i = 0; i < num_bars; i++) {
    cin >> cost[i];
  }

  vector<vector<pair<int, int>>> result;
  for (int i = 0; i < num_bars; i++) {
    vector<pair<int, int>> temp_v;
    for (int j = 0; j <= weight; j++) {
      pair<int, int> temp_p;
      temp_p.first = -1;
      temp_p.second = -1;
      temp_v.push_back(temp_p);
    }
    result.push_back(temp_v);
  }
  result[0][0].first = 0;
  result[0][0].second = 0;

  for (int i = 0; i < num_bars; i++) {
    for (int j = weight; j >= 0; j--) {
      if (i != 0 && j == weight) {
        for (int k = 0; k <= weight; k++) {
          result[i][k] = result[i - 1][k];
        }
      }

      if (result[i][j].first != -1 && j + things[i] <= weight &&
          result[i][j].first + cost[i] > result[i][j + things[i]].first) {
        result[i][j + things[i]].first = result[i][j].first + cost[i];
        result[i][j + things[i]].second = i;
      }
    }
  }

  int max_cost = 0;
  int current_weight = 0;
  for (int i = weight; i >= 0; i--) {
    if (result[num_bars - 1][i].first > max_cost) {
      max_cost = result[num_bars - 1][i].first;
      current_weight = i;
    }
  }

  vector<int> sequence;
  for (int i = num_bars - 1; i >= 0 && current_weight > 0; i--) {
    if (result[i][current_weight].second == i) {
      sequence.push_back(i);
      current_weight -= things[i];
    }
  }

  sort(sequence.begin(), sequence.end());
  for (auto x : sequence) {
    cout << x + 1 << endl;
  }

  delete[] cost;
  delete[] things;

  return 0;
}