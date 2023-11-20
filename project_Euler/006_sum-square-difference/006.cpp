#include <iostream>
#include <numeric>
#include <ranges>

namespace {

unsigned long long sum_of_squares(unsigned n) {
  auto &&squares = std::views::iota(1u, n + 1) |
                   std::views::transform([](auto i) { return i * i; });
  return std::accumulate(squares.begin(), squares.end(), 0ull,
                         std::plus<unsigned long long>{});
}

unsigned long long square_of_sum(unsigned n) {
  auto range = std::views::iota(1u, n + 1);
  auto sum = std::accumulate(range.begin(), range.end(), 0ull,
                             std::plus<unsigned long long>{});
  return sum * sum;
}

} // namespace

int main() {
  std::cout << square_of_sum(100) - sum_of_squares(100) << std::endl;
}
