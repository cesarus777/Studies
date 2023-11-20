#include <concepts>
#include <iostream>
#include <vector>

#define ever ;;

template <std::integral T> constexpr T sum_even_fibs(T limit) {
  T prev_prev = 2;
  T prev = 8;
  std::vector<T> even_fibs = {prev_prev, prev};
  T sum = prev_prev + prev;
  for (ever) {
    even_fibs.emplace_back(4 * prev + prev_prev);
    prev_prev = prev;
    prev = even_fibs.back();
    if (prev > limit)
        return sum;
    sum += prev;
  }
}

int main() { std::cout << sum_even_fibs(4'000'000) << std::endl; }
