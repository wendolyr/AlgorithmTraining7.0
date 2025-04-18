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

  int find_nearest_right(int position, int value) {
    if (value > values[0]) return -1;

    int result = find_nearest_right(position - 1, value, 0, size / 2, size - 1);

    return result;
  }

  int find_nearest_right(int index, int value, int node, int node_l,
                         int node_r) {
    if (node_r - size / 2 < index ||
        (node_l == node_r && node_l - size / 2 < index) ||
        values[node] < value) {
      return -1;
    }

    if (node_l == node_r && values[node] >= value) {
      return node - size / 2 + 1;
    } else if (node_l == node_r && values[node] < value) {
      return -1;
    }

    int find_position = find_nearest_right(index, value, 2 * node + 1, node_l,
                                           (node_l + node_r) / 2);
    if (find_position == -1) {
      find_position = find_nearest_right(index, value, 2 * node + 2,
                                         (node_l + node_r) / 2 + 1, node_r);
    }

    return find_position;
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

  cin >> n >> k;
  vector<int> numbers(n);
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  Segment_tree data(numbers);

  for (int i = 0; i < k; i++) {
    int command = -1;
    cin >> command;
    if (command == 1) {
      int position = 0, value = 0;
      cin >> position >> value;
      auto res = data.find_nearest_right(position, value);
      cout << res << endl;
    } else if (command == 0) {
      pair<int, int> new_value;
      cin >> new_value.first >> new_value.second;
      data.change_value(new_value.first, new_value.second);
    }
  }

  return 0;
}