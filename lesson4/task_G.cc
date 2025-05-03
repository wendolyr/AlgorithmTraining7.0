#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> v;
  int city_number;

 public:
  DSU(int n) : v(n, 0), city_number(n) {
    for (int i = 0; i < n; i++) {
      v[i] = i;
    }
  }

  int get_number() { return city_number; }

  int find_set(int a) {
    if (a == v[a]) return a;
    return find_set(v[a]);
  }

  bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      v[b] = a;
      city_number--;
      return true;
    }
    return false;
  }
};

int main() {
  int n = 0, m = 0;
  std::cin >> n >> m;

  std::vector<std::pair<int, int>> bridges(m);
  for (int i = 0; i < m; i++) {
    std::cin >> bridges[i].first >> bridges[i].second;
    bridges[i].first--;
    bridges[i].second--;
  }

  int counter = 0;
  DSU sets(n);
  for (int i = 0; i < m && counter == 0; i++) {
    if (sets.union_sets(bridges[i].first, bridges[i].second)) {
      if (sets.get_number() == 1) {
        counter = i + 1;
      }
    }
  }

  std::cout << counter << std::endl;

  return 0;
}