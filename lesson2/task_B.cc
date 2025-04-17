#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Segment_tree {
 private:
  int size;
  vector<int> values;
  vector<int> indexes;

 public:
  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);
    indexes.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
      indexes[i] = i - middle;
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = INT_MIN;
      indexes[i] = i - middle;
    }

    for (int i = middle - 1; i >= 0; i--) {
      int l_child = 2 * i + 1;
      int r_child = 2 * i + 2;
      values[i] = max(values[l_child], values[r_child]);
      if (values[l_child] >= values[r_child]) {
        indexes[i] = indexes[l_child];
      } else {
        indexes[i] = indexes[r_child];
      }
    }
  }

  int segment_ind_max(int left, int right) {
    return segment_ind_max(size / 2 + left - 1, size / 2 + right - 1, 0,
                           size / 2, size - 1)
               .second +
           1;
  }

  pair<int, int> segment_ind_max(int left, int right, int node, int node_l,
                                 int node_r) {
    if (node_l > right || node_r < left) return {INT_MIN, 0};
    if (node_l >= left && node_r <= right) {
      return {values[node], indexes[node]};
    }

    auto l_child = segment_ind_max(left, right, 2 * node + 1, node_l,
                                   (node_l + node_r) / 2);
    auto r_child = segment_ind_max(left, right, 2 * node + 2,
                                   (node_l + node_r) / 2 + 1, node_r);

    pair<int, int> result;

    if (l_child.first >= r_child.first) {
      result = l_child;
    } else {
      result = r_child;
    }

    return result;
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
  vector<pair<int, int>> segments(k);
  for (int i = 0; i < k; i++) {
    cin >> segments[i].first >> segments[i].second;
  }

  Segment_tree data(numbers);

  for (int i = 0; i < k; i++) {
    cout << data.segment_ind_max(segments[i].first, segments[i].second) << endl;
  }

  return 0;
}