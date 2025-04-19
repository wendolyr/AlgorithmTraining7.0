#include <climits>
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  int longest_null_seq;
  int null_prefix;
  int null_suffix;
  bool all_null;
  int seq_size;
} Data_t;

class Segment_tree {
 private:
  int size;
  vector<int> values;
  vector<int> longest_null_seq;
  vector<int> null_prefix;
  vector<int> null_suffix;
  vector<bool> all_null;
  vector<int> seq_size;

  void calculate_params(int i) {
    int l_child = 2 * i + 1;
    int r_child = 2 * i + 2;

    if (all_null[l_child] && all_null[r_child]) {
      all_null[i] = true;
    } else {
      all_null[i] = false;
    }

    seq_size[i] = seq_size[l_child] + seq_size[r_child];

    values[i] = max(values[l_child], values[r_child]);

    longest_null_seq[i] =
        max(longest_null_seq[l_child], longest_null_seq[r_child]);

    int temp = 0;
    temp += all_null[l_child] ? seq_size[l_child] : 0;
    temp += all_null[r_child] ? seq_size[r_child] : 0;
    if (!all_null[l_child]) {
      temp += null_suffix[l_child];
    }
    if (!all_null[r_child]) {
      temp += null_prefix[r_child];
    }
    longest_null_seq[i] = max(longest_null_seq[i], temp);

    if (!all_null[i]) {
      null_prefix[i] = all_null[l_child] ? seq_size[l_child] : 0;
      if (null_prefix[i] == 0) {
        null_prefix[i] = null_prefix[l_child];
      } else {
        null_prefix[i] += null_prefix[r_child];
      }

      null_suffix[i] = all_null[r_child] ? seq_size[r_child] : 0;
      if (null_suffix[i] == 0) {
        null_suffix[i] = null_suffix[r_child];
      } else {
        null_suffix[i] += null_suffix[l_child];
      }
    }
  }

 public:
  void print_class() {
    for (auto x : values) {
      cout << x << ' ';
    }
    cout << endl;
    for (auto x : longest_null_seq) {
      cout << x << ' ';
    }
    cout << endl;
    for (auto x : all_null) {
      cout << x << ' ';
    }
    cout << endl;
    for (auto x : null_prefix) {
      cout << x << ' ';
    }
    cout << endl;
    for (auto x : null_suffix) {
      cout << x << ' ';
    }
    cout << endl;
  }

  Segment_tree(const vector<int>& n) {
    size = 1;
    while (size < (int)n.size()) {
      size <<= 1;
    }
    size = 2 * size - 1;
    values.resize(size, 0);
    longest_null_seq.resize(size, 0);
    null_prefix.resize(size, 0);
    null_suffix.resize(size, 0);
    all_null.resize(size, false);
    seq_size.resize(size, 0);

    int middle = size / 2;
    for (size_t i = middle; i < middle + n.size(); i++) {
      values[i] = n[i - middle];
      if (values[i] == 0) {
        longest_null_seq[i] = 1;
        all_null[i] = true;
        seq_size[i] = 1;
      }
    }

    for (int i = middle + n.size(); i < size; i++) {
      values[i] = INT_MIN;
      seq_size[i] = 1;
    }

    for (int i = middle - 1; i >= 0; i--) {
      calculate_params(i);
    }
  }

  void change_value(int ind, int val) {
    ind--;
    int tree_ind = ind + size / 2;
    int change = 0;
    if (val == 0 && values[tree_ind] != 0) {
      change = 1;
      all_null[tree_ind] = true;
      longest_null_seq[tree_ind] = 1;
      seq_size[tree_ind] = 1;
    } else if (val != 0 && values[tree_ind] == 0) {
      change = 1;
      all_null[tree_ind] = false;
      longest_null_seq[tree_ind] = 0;
      seq_size[tree_ind] = 1;
    }

    values[tree_ind] = val;

    while (tree_ind > 0) {
      tree_ind = (tree_ind - 1) / 2;
      if (change) {
        calculate_params(tree_ind);
      } else {
        int l_child = 2 * tree_ind + 1;
        int r_child = 2 * tree_ind + 2;
        values[tree_ind] = max(values[l_child], values[r_child]);
      }
    }
  }

  int find_max_seq(int left, int right) {
    left--;
    right--;
    auto result =
        find_max_seq(left + size / 2, right + size / 2, 0, size / 2, size - 1);

    return result.longest_null_seq;
  }

  Data_t find_max_seq(int left, int right, int node, int node_l, int node_r) {
    if (left > node_r || right < node_l) {
      return {0, 0, 0, 0, 0};
    }
    if (node_l >= left && node_r <= right) {
      return {longest_null_seq[node], null_prefix[node], null_suffix[node],
              all_null[node], seq_size[node]};
    }

    auto l_child =
        find_max_seq(left, right, 2 * node + 1, node_l, (node_l + node_r) / 2);
    auto r_child = find_max_seq(left, right, 2 * node + 2,
                                (node_l + node_r) / 2 + 1, node_r);

    Data_t d = {0, 0, 0, 0, 0};
    d.seq_size = l_child.seq_size + r_child.seq_size;
    d.longest_null_seq =
        max(l_child.longest_null_seq, r_child.longest_null_seq);
    int temp = 0;
    if (l_child.all_null && r_child.all_null) {
      temp = l_child.longest_null_seq + r_child.longest_null_seq;
      d.all_null = true;
    } else if (l_child.all_null) {
      temp = l_child.longest_null_seq + r_child.null_prefix;
      d.null_prefix = l_child.seq_size + r_child.null_prefix;
      d.null_suffix = r_child.null_suffix;
    } else if (r_child.all_null) {
      temp = l_child.null_suffix + r_child.longest_null_seq;
      d.null_prefix = l_child.null_prefix;
      d.null_suffix = l_child.null_suffix + r_child.seq_size;
    } else {
      temp = l_child.null_suffix + r_child.null_prefix;
      d.null_prefix = l_child.null_prefix;
      d.null_suffix = r_child.null_suffix;
    }

    d.longest_null_seq = max(d.longest_null_seq, temp);

    return d;
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
    string command;
    cin >> command;
    if (command == "QUERY") {
      pair<int, int> query;
      cin >> query.first >> query.second;
      int result = data.find_max_seq(query.first, query.second);
      cout << result << endl;
    } else if (command == "UPDATE") {
      pair<int, int> new_value;
      cin >> new_value.first >> new_value.second;
      data.change_value(new_value.first, new_value.second);
    }
  }

  return 0;
}