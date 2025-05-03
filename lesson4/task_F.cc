#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> v;

 public:
  DSU(int n) : v(n, 0) {
    for (int i = 0; i < n; i++) {
      v[i] = i;
    }
  }

  int find_set(int a) {
    if (a == v[a]) return a;
    return find_set(v[a]);
  }

  bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      v[b] = a;
      return true;
    }
    return false;
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> piggy_banks(n);
  for (int i = 0; i < n; i++) {
    std::cin >> piggy_banks[i];
    piggy_banks[i]--;
  }

  DSU sets(n);
  int counter = 0;

  for (int i = 0; i < n; i++) {
    if (!sets.union_sets(i, piggy_banks[i])) {
      counter++;
    }
  }

  std::cout << counter << std::endl;
}