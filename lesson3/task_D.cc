#include <iostream>

using namespace std;

int main() {
  short n = 0;
  cin >> n;
  short temp = n;
  short size = 0;
  while (temp != 0) {
    size++;
    temp >>= 1;
  }

  short max = 0;
  short counter = size;

  while (counter) {
    short first_bit = n & 1;
    n >>= 1;
    if (first_bit) {
      n |= first_bit << (size - 1);
    } else {
      n &= ~(first_bit << (size - 1));
    }
    if (n > max) {
      max = n;
    }
    counter--;
  }

  cout << max;

  return 0;
}