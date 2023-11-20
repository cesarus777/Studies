#include <concepts>
#include <iostream>

namespace {

constexpr bool is_palindrome(std::integral auto n) {
  auto n_str = std::to_string(n);
  auto size = n_str.size();
  for (size_t i = 0; i < size / 2; ++i) {
    if (n_str[i] != n_str[size - i - 1])
      return false;
  }
  return true;
}

} // namespace

int main() {
  unsigned long long largest = 0;
  for (size_t i = 999; i >= 100; --i)
    for (size_t j = 999; j >= i; --j)
      if (is_palindrome(i * j) && (largest < i * j))
        largest = i * j;
  std::cout << largest << std::endl;
}
