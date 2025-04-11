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

  bool *result = new bool[weight + 1];
  for (int i = 0; i <= weight; i++) {
    result[i] = false;
  }
  result[0] = true;

  for (int i = 0; i < num_bars; i++) {
    for (int j = weight; j >= 0; j--) {
      if (result[j] == true && j + things[i] <= weight) {
        result[j + things[i]] = true;
      }
    }
  }

  for (int i = weight; i >= 0; i--) {
    if (result[i] == true) {
      cout << i;
      i = -1;
    }
  }

  delete[] things;
  delete[] result;
  return 0;
}