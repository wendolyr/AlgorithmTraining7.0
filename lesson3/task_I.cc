#include <iostream>

using namespace std;

void sendPack() {
  string pack;
  cin >> pack;

  for (char c : pack) {
    cout << c << c << c;
  }
}

void getPack() {
  string pack;
  cin >> pack;
  int final_bit = 0;
  int counter = 0;
  for (size_t i = 0; i < pack.size(); i++) {
    if (pack[i] == '1') {
      final_bit += 1;
    }
    counter++;
    if (counter == 3) {
      cout << final_bit / 2;
      counter = 0;
      final_bit = 0;
    }
  }
}

int main() {
  int option = 0;
  cin >> option;
  if (option == 1) {
    sendPack();
  } else if (option == 2) {
    getPack();
  }

  return 0;
}