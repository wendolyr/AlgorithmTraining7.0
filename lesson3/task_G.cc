#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
 private:
  vector<long long> data;
  int size;

 public:
  FenwickTree(int n) : data(n, 0), size(n) {}

  void update(int index, long long value) {
    while (index < size) {
      data[index] += value;
      index |= (index + 1);
    }
  }

  long long sum(int l, int r) { return sum(r) - sum(l - 1); }

  long long sum(int index) {
    long long sum = 0;
    while (index >= 0) {
      sum += data[index];
      index &= (index + 1);
      index--;
    }

    return sum;
  }
};

int main() {
  int n = 0, k = 0;
  cin >> n >> k;

  FenwickTree t(n);
  vector<long long> a(n, 0);

  for (int i = 0; i < k; i++) {
    char command = ' ';
    cin >> command;

    if (command == 'A') {
      int ind = 0;
      long long value = 0;
      cin >> ind >> value;
      ind--;
      long long diff = value - a[ind];
      a[ind] = value;
      t.update(ind, diff);
    } else if (command == 'Q') {
      int l = 0, r = 0;
      cin >> l >> r;
      l--;
      r--;
      cout << t.sum(l, r) << endl;
    }
  }

  return 0;
}