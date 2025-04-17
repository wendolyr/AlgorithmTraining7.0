#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Segment_tree {
 private:
  int size;
  vector<int> values;

 public:
  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = INT_MIN;
    }

    for (int i = middle - 1; i >= 0; i--) {
      int l_child = 2 * i + 1;
      int r_child = 2 * i + 2;
      values[i] = max(values[l_child], values[r_child]);
    }
  }

  int segment_max(int left, int right) {
    return segment_max(size / 2 + left - 1, size / 2 + right - 1, 0, size / 2,
                       size - 1);
  }

  int segment_max(int left, int right, int node, int node_l, int node_r) {
    if (node_l > right || node_r < left) return INT_MIN;
    if (node_l >= left && node_r <= right) {
      return values[node];
    }

    auto l_child =
        segment_max(left, right, 2 * node + 1, node_l, (node_l + node_r) / 2);
    auto r_child = segment_max(left, right, 2 * node + 2,
                               (node_l + node_r) / 2 + 1, node_r);

    return max(l_child, r_child);
  }

  void change_value(int ind, int val) {
    ind--;
    int tree_ind = ind + size / 2;
    values[tree_ind] = val;

    while (tree_ind > 0) {
      tree_ind = (tree_ind - 1) / 2;
      int l_child = 2 * tree_ind + 1;
      int r_child = 2 * tree_ind + 2;
      values[tree_ind] = max(values[l_child], values[r_child]);
    }
  }
};

int main() {
  int n = 0, k = 0;

  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  cin >> k;

  Segment_tree data(numbers);

  for (int i = 0; i < k; i++) {
    char command;
    cin >> command;
    if (command == 's') {
      pair<int, int> segment;
      cin >> segment.first >> segment.second;
      auto res = data.segment_max(segment.first, segment.second);
      cout << res << ' ';
    } else if (command == 'u') {
      pair<int, int> new_value;
      cin >> new_value.first >> new_value.second;
      data.change_value(new_value.first, new_value.second);
    }
  }

  return 0;
}