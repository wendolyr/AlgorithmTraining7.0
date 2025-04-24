#include <iostream>

int main() {
  unsigned long long x = 0;
  std::cin >> x;
  int counter = 0;
  while (x > 0) {
    int temp = 1;
    temp &= x;
    if (temp) counter++;
    x >>= 1;
  }

  std::cout << counter;

  return 0;
}