#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>

#ifdef NAIVE

constexpr bool is_multiple_of(unsigned long long n, unsigned long long base) {
  return (n % base) == 0;
}

constexpr bool is3or5multiple(unsigned long long n) {
  return is_multiple_of(n, 3) || is_multiple_of(n, 5);
}

int main() {
  auto &&sum_to_1000_range =
      std::views::iota(0, 1000) | std::views::filter(&is3or5multiple);
  auto sum_to_1000 = std::accumulate(sum_to_1000_range.begin(),
                                     sum_to_1000_range.end(), 0, std::plus{});
  std::cout << sum_to_1000 << std::endl;
}

#else

constexpr auto sum3or5multimples(std::integral auto limit) {
  auto num3multiples = (limit - 1) / 3;
  auto num5multiples = (limit - 1) / 5;
  auto num3and5multiples = (limit - 1) / 15;

  // Arithmetic progression
  auto sum_multiples = [](auto num_multiples) {
    return (num_multiples + 1) * num_multiples / 2;
  };

  auto sum3multiples = sum_multiples(num3multiples);
  auto sum5multiples = sum_multiples(num5multiples);
  auto sum3and5multiples = sum_multiples(num3and5multiples);

  // Both 3 and 5 multiples are counted two times
  return 3 * sum3multiples + 5 * sum5multiples - 15 * sum3and5multiples;
}

int main() { std::cout << sum3or5multimples(1000) << std::endl; }

#endif
