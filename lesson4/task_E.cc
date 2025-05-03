#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> elimination(n, 0);
  std::vector<int> left(n), right(n);
  std::queue<int> q;

  for (int i = 0; i < n; i++) {
    left[i] = (i - 1 + n) % n;
    right[i] = (i + 1) % n;
  }

  for (int i = 0; i < n; i++) {
    if (a[i] < a[left[i]] && a[i] < a[right[i]]) {
      q.push(i);
    }
  }

  int current_round = 1;
  while (n > 2 && !q.empty()) {
    int size = q.size();
    for (int i = 0; i < size; i++) {
      int elem = q.front();
      q.pop();

      if (elimination[elem] != 0) continue;
      if (a[elem] < a[left[elem]] && a[elem] < a[right[elem]]) {
        elimination[elem] = current_round;
        n--;

        int l = left[elem], r = right[elem];
        right[l] = r;
        left[r] = l;

        if (elimination[l] == 0 && a[l] < a[left[l]] && a[l] < a[right[l]]) {
          q.push(l);
        }
        if (elimination[r] == 0 && a[r] < a[left[r]] && a[r] < a[right[r]]) {
          q.push(r);
        }
      }
    }
    current_round++;
  }

  for (int i : elimination) {
    std::cout << i << ' ';
  }

  return 0;
}