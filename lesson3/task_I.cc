#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encode(const string &x) {
  int n = x.size();
  int k = 0;
  while ((1 << k) < n + k + 1) k++;
  string y(n + k, '0');
  int j = 0;
  for (int i = 1; i <= n + k; i++) {
    if ((i & (i - 1)) != 0) {
      y[i - 1] = x[j++];
    }
  }

  for (int i = 0; i < k; i++) {
    int control_bit = (1 << i);
    int counter = 0;
    for (int q = control_bit + 1; q <= n + k; q++) {
      if ((control_bit & q) != 0 && y[q - 1] == '1') {
        counter++;
      }
    }
    y[control_bit - 1] = counter % 2 == 0 ? '0' : '1';
  }

  return y;
}

string decode(const string &z) {
  int n = z.size();
  int k = 0;
  while ((1 << k) < n + 1) k++;

  int error_pos = 0;
  for (int i = 0; i < k; i++) {
    int control_bit = (1 << i);
    int counter = 0;
    for (int q = control_bit + 1; q <= n + k; q++) {
      if ((control_bit & q) != 0 && z[q - 1] == '1') {
        counter++;
      }
    }
    char check = counter % 2 == 0 ? '0' : '1';
    if (z[control_bit - 1] != check) {
      error_pos += control_bit;
    }
  }

  string y = z;
  if (error_pos > 0 && error_pos <= n) {
    y[error_pos - 1] = (y[error_pos - 1] == '1' ? '0' : '1');
  }

  string x;
  for (int i = 0; i <= n; i++) {
    if ((i & (i - 1)) != 0) {
      x += y[i - 1];
    }
  }
  return x;
}

int main() {
  int run;
  cin >> run;
  cin.ignore();
  string data;
  getline(cin, data);
  if (run == 1)
    cout << encode(data) << endl;
  else if (run == 2)
    cout << decode(data) << endl;
  return 0;
}