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

  int res = a[0];
  for (int i = 1; i < n; i++) {
    res ^= a[i];
  }

  if (res == 0) {
    for (auto x : a) {
      cout << x << ' ';
    }
    return 0;
  } else {
    unsigned long long min = a[0];
    for (int i = 1; i < n; i++) {
      if (a[i] < min) {
        min = a[i];
      }
    }
    if (min == 1) {
      cout << "impossible";
      return 0;
    }
  }

  for (int i = 0; i < max_bits; i++) {
    int sum_bit = 0;
    for (int j = 0; j < n; j++) {
      if (a[j] & (1 << i)) {
        sum_bit++;
      }
    }

    if (sum_bit % 2 == 1) {
      int finder = -1;
      int new_sum = 0;
      for (int j = i + 1; j < max_bits; j++) {
        for (int k = 0; k < n; k++) {
          if (a[k] & (1 << j)) {
            new_sum++;
          }
        }
        if (new_sum % 2 == 1) {
          finder = j;
          break;
        }
      }
      if (finder == -1) {
        cout << "impossible";
        return 0;
      } else {
        for (int j = 0; j < n; j++) {
          if ((a[j] & (1 << i)) && !(a[j] & (1 << finder))) {
            a[j] &= ~(1ULL << i);
            a[j] |= 1ULL << finder;
            break;
          } else if (!(a[j] & (1 << i)) && (a[j] & (1 << finder))) {
            a[j] &= ~(1ULL << finder);
            a[j] |= 1ULL << i;
            break;
          }
        }
      }
    }
  }

  for (auto x : a) {
    cout << x << ' ';
  }

  return 0;
}