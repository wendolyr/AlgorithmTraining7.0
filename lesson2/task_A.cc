#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Segment_tree {
 private:
  int size;
  vector<int> values;
  vector<int> counter;

 public:
  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);
    counter.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
      counter[i] = 1;
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = INT_MIN;
      counter[i] = 0;
    }

    for (int i = middle - 1; i >= 0; i--) {
      int l_child = 2 * i + 1;
      int r_child = 2 * i + 2;
      values[i] = max(values[l_child], values[r_child]);
      if (values[l_child] == values[r_child]) {
        counter[i] = counter[l_child] + counter[r_child];
      } else if (values[l_child] > values[r_child]) {
        counter[i] = counter[l_child];
      } else {
        counter[i] = counter[r_child];
      }
    }
  }

  pair<int, int> segment_max(int left, int right) {
    return segment_max(size / 2 + left - 1, size / 2 + right - 1, 0, size / 2,
                       size - 1);
  }

  pair<int, int> segment_max(int left, int right, int node, int node_l,
                             int node_r) {
    if (node_l > right || node_r < left) return {INT_MIN, 0};
    if (node_l >= left && node_r <= right) {
      return {values[node], counter[node]};
    }

    pair<int, int> l_child =
        segment_max(left, right, 2 * node + 1, node_l, (node_l + node_r) / 2);
    pair<int, int> r_child = segment_max(left, right, 2 * node + 2,
                                         (node_l + node_r) / 2 + 1, node_r);

    pair<int, int> result;
    if (l_child.first > r_child.first) {
      result = l_child;
    } else if (l_child.first < r_child.first) {
      result = r_child;
    } else {
      result.first = l_child.first;
      result.second = l_child.second + r_child.second;
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
    auto res = data.segment_max(segments[i].first, segments[i].second);
    cout << res.first << ' ' << res.second << endl;
  }
}