#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n = 0;
  cin >> n;

  vector<unsigned long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  unsigned long long result = a[0];

  for (int i = 1; i < n; i++) {
    result ^= a[i];
  }

  if (!result) {
    for (int i = 0; i < n; i++) {
      cout << a[i] << ' ';
    }
  } else {
    unsigned long long max = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] > max) {
        max = a[i];
      }
    }

    int counter = 0;
    while (max != 0) {
      max >>= 1;
      counter++;
    }

    for (int i = 0; i <) }

  return 0;
}