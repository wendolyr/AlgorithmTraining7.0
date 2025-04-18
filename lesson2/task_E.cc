#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Segment_tree {
 private:
  int size;
  vector<int> values;
  vector<int> null_counter;

  int counting_nulls(int left, int right, int node, int node_l, int node_r) {
    if (node_l > right || node_r < left) return 0;
    if (node_l >= left && node_r <= right) {
      return null_counter[node];
    }
    int result = counting_nulls(left, right, 2 * node + 1, node_l,
                                (node_l + node_r) / 2) +
                 counting_nulls(left, right, 2 * node + 2,
                                (node_l + node_r) / 2 + 1, node_r);

    return result;
  }

  int find_null(int node, int node_l, int node_r, int position) {
    if (node_l == node_r) {
      return (node - size / 2) + 1;
    }
    if (position <= null_counter[2 * node + 1]) {
      return find_null(2 * node + 1, node_l, (node_l + node_r) / 2, position);
    } else {
      return find_null(2 * node + 2, (node_l + node_r) / 2 + 1, node_r,
                       position - null_counter[2 * node + 1]);
    }
  }

 public:
  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);
    null_counter.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
      if (values[i] == 0) {
        null_counter[i] = 1;
      }
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = INT_MIN;
    }

    for (int i = middle - 1; i >= 0; i--) {
      int l_child = 2 * i + 1;
      int r_child = 2 * i + 2;
      values[i] = max(values[l_child], values[r_child]);
      null_counter[i] = null_counter[l_child] + null_counter[r_child];
    }
  }

  int find_null(int left, int right, int position) {
    int massive_begin_ind = size / 2;
    int massive_end_ind = size - 1;
    left--;
    right--;

    int nulls_in_segment =
        counting_nulls(massive_begin_ind + left, massive_begin_ind + right, 0,
                       massive_begin_ind, massive_end_ind);

    if (position > nulls_in_segment) {
      return -1;
    }

    int nulls_before = 0;
    if (massive_begin_ind <= massive_begin_ind + left - 1)
      nulls_before =
          counting_nulls(massive_begin_ind, massive_begin_ind + left - 1, 0,
                         massive_begin_ind, massive_end_ind);

    return find_null(0, massive_begin_ind, massive_end_ind,
                     position + nulls_before);
  }

  void change_value(int ind, int val) {
    ind--;
    int tree_ind = ind + size / 2;
    values[tree_ind] = val;

    int change = 0;
    int temp = null_counter[tree_ind];
    null_counter[tree_ind] = val == 0 ? 1 : 0;

    if (temp == 0 && null_counter[tree_ind] == 1) {
      change = 1;
    } else if (temp == 1 && null_counter[tree_ind] == 0) {
      change = -1;
    }

    while (tree_ind > 0) {
      tree_ind = (tree_ind - 1) / 2;
      int l_child = 2 * tree_ind + 1;
      int r_child = 2 * tree_ind + 2;
      values[tree_ind] = max(values[l_child], values[r_child]);
      null_counter[tree_ind] += change;
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
      int index = 0;
      cin >> segment.first >> segment.second >> index;
      auto res = data.find_null(segment.first, segment.second, index);
      cout << res << ' ';
    } else if (command == 'u') {
      pair<int, int> new_value;
      cin >> new_value.first >> new_value.second;
      data.change_value(new_value.first, new_value.second);
    }
  }

  return 0;
}