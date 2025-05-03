#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore();

  std::vector<std::string> history;
  std::vector<std::string> windows_order;
  for (int i = 0; i < n; i++) {
    std::string command;
    std::getline(std::cin, command);
    if (command.substr(0, 3) == "Run") {
      if (command.size() == 3) {
        windows_order.insert(windows_order.begin(), "");
        history.push_back("");
        continue;
      }
      std::string app = command.substr(4);
      windows_order.insert(windows_order.begin(), app);
      history.push_back(app);
    } else {
      if (windows_order.size() == 0) continue;
      int alt_count = std::count(command.begin(), command.end(), 'T');
      int running_apps = windows_order.size();

      int window_pos = alt_count % running_apps;
      std::string window_name = windows_order[window_pos];
      history.push_back(window_name);
      windows_order.erase(windows_order.begin() + window_pos);
      windows_order.insert(windows_order.begin(), window_name);
    }
  }

  for (auto &i : history) {
    std::cout << i << std::endl;
  }

  return 0;
}