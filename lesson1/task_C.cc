#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define TYPE 30
using namespace std;

int main() {
  long long m = 0;
  cin >> m;

  vector<long long> a(31);
  for (int i = 0; i <= TYPE; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= TYPE; i++) {
    if (2 * a[i - 1] - a[i] > 0) {
      a[i] = 2 * a[i - 1];
    }
  }

  long long result = LLONG_MAX, cost = 0;

  for (int i = TYPE; i >= 0; i--) {
    if (m <= a[i]) {
      result = min(result, cost + (1LL << i));
    } else {
      cost += 1LL << i;
      m -= a[i];
    }
  }

  cout << result << endl;

  return 0;
}