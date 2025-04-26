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

  unsigned long long max = a[0];

  for (int i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  int max_bits = 0;
  while (max) {
    max_bits++;
    max >>= 1;
  }

  return 0;
}