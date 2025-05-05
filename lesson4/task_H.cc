#include <iostream>
#include <map>
#include <string>
#include <vector>

class DSU {
 private:
  std::vector<int> v;
  std::vector<int> lenght;

 public:
  DSU(int n) : v(n, 0), lenght(n, 1) {
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
      if (lenght[a] > lenght[b]) {
        std::swap(a, b);
      }
      lenght[b] += lenght[a];
      v[a] = b;
      return true;
    }
    return false;
  }

  bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
};

int main() {
  int n{}, m{}, k{};
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, int>> ribs(m);
  for (int i = 0; i < m; i++) {
    std::cin >> ribs[i].first >> ribs[i].second;
    ribs[i].first--;
    ribs[i].second--;
  }

  std::vector<std::pair<std::string, std::pair<int, int>>> history(k);
  for (int i = 0; i < k; i++) {
    std::cin >> history[i].first >> history[i].second.first >>
        history[i].second.second;
    history[i].second.first--;
    history[i].second.second--;
  }

  DSU sets(n);

  std::vector<std::string> answers;
  for (int i = k - 1; i >= 0; i--) {
    if (history[i].first == "ask") {
      if (sets.is_connected(history[i].second.first,
                            history[i].second.second)) {
        answers.push_back("YES");
      } else {
        answers.push_back("NO");
      }
    } else if (history[i].first == "cut") {
      sets.union_sets(history[i].second.first, history[i].second.second);
    }
  }

  for (auto it = answers.rbegin(); it != answers.rend(); it++) {
    std::cout << *it << std::endl;
  }

  return 0;
}