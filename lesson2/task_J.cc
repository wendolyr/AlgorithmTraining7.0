#include <climits>
#include <iostream>
#include <vector>

#define K 55
#define MOD (long long)(1e9 + 4)

using namespace std;

class Segment_tree {
 private:
  int size;
  vector<long long> values;
  vector<long long> promises;
  vector<long long> hash;

 public:
  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);
    promises.resize(size, 0);
    hash.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
      hash[i] = (hash[i] + K * values[i]) % MOD;
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = LLONG_MIN;
      hash[i] = (hash[2 * i + 1] + hash[2 * i + 2]);
    }

    for (int i = middle - 1; i >= 0; i--) {
      int l_child = 2 * i + 1;
      int r_child = 2 * i + 2;
      values[i] = max(values[l_child], values[r_child]);
    }
  }

  void add_to_data(int value, int left, int right) {
    left--;
    right--;
    add_to_data(value, left + size / 2, right + size / 2, 0, size / 2,
                size - 1);
  }

  void add_to_data(int value, int left, int right, int node, int node_l,
                   int node_r) {
    if (node_l > right || node_r < left) {
      return;
    }
    if (node_l >= left && node_r <= right) {
      values[node] += value;
      promises[node] += value;
      return;
    }

    add_to_data(value, left, right, 2 * node + 1, node_l,
                (node_l + node_r) / 2);
    add_to_data(value, left, right, 2 * node + 2, (node_l + node_r) / 2 + 1,
                node_r);

    values[node] = max(values[2 * node + 1] + promises[node],
                       values[2 * node + 2] + promises[node]);
  }

  long long find_max(int left, int right) {
    left--;
    right--;

    return find_max(left + size / 2, right + size / 2, 0, size / 2, size - 1);
  }

  long long find_max(int left, int right, int node, int node_l, int node_r) {
    if (node_l > right || node_r < left) {
      return LLONG_MIN;
    }

    if (node_l >= left && node_r <= right) {
      return values[node];
    }

    if (promises[node]) {
      promises[2 * node + 1] += promises[node];
      promises[2 * node + 2] += promises[node];
      values[2 * node + 1] += promises[node];
      values[2 * node + 2] += promises[node];
      promises[node] = 0;
    }

    long long l_child =
        find_max(left, right, 2 * node + 1, node_l, (node_l + node_r) / 2);
    long long r_child =
        find_max(left, right, 2 * node + 2, (node_l + node_r) / 2 + 1, node_r);

    return max(l_child, r_child);
  }
};

int main() {
  int n = 0, k = 0;

  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; i++) {
    cin >> numbers[i];
  }

  Segment_tree data(numbers);

  cin >> k;

  for (int i = 0; i < k; i++) {
    char command = ' ';
    cin >> command;
    if (command == 'm') {
      pair<int, int> range;
      cin >> range.first >> range.second;
      cout << data.find_max(range.first, range.second) << ' ';
    } else if (command == 'a') {
      pair<int, int> range;
      int add = 0;
      cin >> range.first >> range.second >> add;
      data.add_to_data(add, range.first, range.second);
    }
  }

  return 0;
}