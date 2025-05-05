#include <iostream>
#include <list>

int main() {
  int n{};
  std::cin >> n;
  std::list<long long> companies;
  long long summ{};
  for (int i = 0; i < n; i++) {
    int a{};
    std::cin >> a;
    companies.push_back(a);
    summ += a * a;
  }

  std::cout << summ << std::endl;

  int k{};
  std::cin >> k;

  int counter = 1;
  auto iter1 = companies.begin();
  for (int i = 0; i < k; i++) {
    int e{}, v{};
    std::cin >> e >> v;

    if (counter < v) {
      for (; iter1 != companies.end(); iter1++) {
        if (counter == v) {
          break;
        }
        counter++;
      }
    } else if (counter > v) {
      for (; iter1 != companies.begin(); iter1--) {
        if (counter == v) {
          break;
        }
        counter--;
      }
    }

    if (e == 1) {
      if (iter1 == companies.begin()) {
        auto right_neighbour_comp = iter1;
        right_neighbour_comp++;
        summ = summ - (*iter1) * (*iter1) -
               (*right_neighbour_comp) * (*right_neighbour_comp);
        *right_neighbour_comp += *iter1;
        summ += (*right_neighbour_comp) * (*right_neighbour_comp);
        companies.erase(iter1);
        iter1 = right_neighbour_comp;
      } else if (iter1 == --companies.end()) {
        auto left_neighbour_comp = iter1;
        left_neighbour_comp--;
        summ = summ - (*iter1) * (*iter1) -
               (*left_neighbour_comp) * (*left_neighbour_comp);
        *left_neighbour_comp += *iter1;
        summ += (*left_neighbour_comp) * (*left_neighbour_comp);
        companies.erase(iter1);
        iter1 = left_neighbour_comp;
        counter--;
      } else {
        auto left_neighbour_comp = iter1;
        left_neighbour_comp--;
        auto right_neighbour_comp = iter1;
        right_neighbour_comp++;
        summ = summ - (*iter1) * (*iter1) -
               (*left_neighbour_comp) * (*left_neighbour_comp) -
               (*right_neighbour_comp) * (*right_neighbour_comp);
        if (*iter1 % 2 == 0) {
          *left_neighbour_comp += *iter1 / 2;
          *right_neighbour_comp += *iter1 / 2;
        } else {
          *left_neighbour_comp += *iter1 / 2;
          *right_neighbour_comp += *iter1 / 2 + 1;
        }

        summ = summ + (*left_neighbour_comp) * (*left_neighbour_comp) +
               (*right_neighbour_comp) * (*right_neighbour_comp);

        companies.erase(iter1);
        iter1 = right_neighbour_comp;
      }

    } else if (e == 2) {
      summ -= (*iter1) * (*iter1);
      if (*iter1 % 2 == 0) {
        long long temp = (*iter1) / 2;
        *iter1 = temp;
        iter1 = companies.insert(iter1, temp);
        summ = summ + temp * temp * 2;
      } else {
        long long left = (*iter1) / 2;
        long long right = (*iter1) / 2 + 1;
        *iter1 = right;
        iter1 = companies.insert(iter1, left);
        summ = summ + left * left + right * right;
      }
    }

    std::cout << summ << std::endl;
  }

  return 0;
}