#include <iostream>
#include <vector>

struct PersistentStack {
  int total_weight;
  PersistentStack *prev;

  PersistentStack(int t, PersistentStack *snowman)
      : total_weight(t), prev(snowman) {}
};

int main() {
  int n{};
  std::cin >> n;

  std::vector<PersistentStack *> snowmans;
  long long result{};

  for (int i = 0; i < n; i++) {
    int t{}, m{};
    std::cin >> t >> m;
    t--;
    PersistentStack *new_snowman = nullptr;
    int new_weight{};

    if (t == -1) {
      new_weight = m;
      new_snowman = new PersistentStack(new_weight, nullptr);
    } else if (m != 0) {
      new_weight = snowmans[t] ? snowmans[t]->total_weight + m : m;
      new_snowman = new PersistentStack(new_weight, snowmans[t]);
    } else {
      new_snowman = snowmans[t]->prev;
      if (new_snowman) {
        new_weight = new_snowman->total_weight;
      }
    }

    snowmans.push_back(new_snowman);
    result += new_weight;
  }

  std::cout << result << std::endl;

  return 0;
}