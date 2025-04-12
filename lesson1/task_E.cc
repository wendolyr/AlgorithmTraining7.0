#include <iostream>

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

  int *result = new int[weight + 1];
  for (int i = 0; i <= weight; i++) {
    result[i] = -1;
  }
  result[0] = 0;

  for (int i = 0; i < num_bars; i++) {
    for (int j = weight; j >= 0; j--) {
      if (result[j] != -1 && j + things[i] <= weight &&
          result[j] + cost[i] > result[j + things[i]]) {
        result[j + things[i]] = result[j] + cost[i];
      }
    }
  }

  int max = 0;

  for (int i = weight; i >= 0; i--) {
    if (result[i] > max) {
      max = result[i];
    }
  }

  cout << max;

  delete[] result;
  delete[] cost;
  delete[] things;

  return 0;
}