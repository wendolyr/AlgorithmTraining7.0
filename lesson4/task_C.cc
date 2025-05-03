#include <deque>
#include <iostream>
#include <stack>

int main() {
  std::string command;
  std::deque<int> st;
  while (std::cin >> command && command != "exit") {
    if (command == "push_back") {
      int n = 0;
      std::cin >> n;
      st.push_back(n);
      std::cout << "ok" << std::endl;
    } else if (command == "push_front") {
      int n = 0;
      std::cin >> n;
      st.push_front(n);
      std::cout << "ok" << std::endl;
    } else if (command == "pop_back") {
      if (st.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << st.back() << std::endl;
        st.pop_back();
      }
    } else if (command == "pop_front") {
      if (st.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << st.front() << std::endl;
        st.pop_front();
      }
    } else if (command == "front") {
      if (st.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << st.front() << std::endl;
      }
    } else if (command == "back") {
      if (st.empty()) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << st.back() << std::endl;
      }
    } else if (command == "size") {
      std::cout << st.size() << std::endl;
    } else if (command == "clear") {
      while (!st.empty()) {
        st.pop_back();
      }
      std::cout << "ok" << std::endl;
    }
  }

  std::cout << "bye" << std::endl;

  return 0;
}