#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

namespace {

class sieve_t final {
  std::vector<bool> primes;
  unsigned long long largest_prime = 2;

  void calc(unsigned long long n) {
    if (n + 2 <= primes.size())
      return;

    primes = std::vector<bool>(n - 1, true);
    for (auto i : std::views::iota(0u, primes.size())) {
      if (!primes[i])
        continue;
      auto curr = i + 2;
      for (auto elem : primes | std::views::drop(i) | std::views::stride(curr) |
                           std::views::drop(1))
        elem = false;
    }
  }

public:
  sieve_t(unsigned long long n) { calc(n); }

  bool is_prime(unsigned long long n) const {
    if (n <= 2)
      return true;

    if (n - 2 >= primes.size())
      return false;
    return primes[n - 2];
  }
};

} // namespace

int main() {
  auto limit = 2'000'000u;
  sieve_t sieve(limit);
  auto &&range = std::views::iota(2u, limit);
  auto sum = std::accumulate(
      range.begin(), range.end(), 0llu,
      [&sieve](auto acc, auto n) { return acc + (sieve.is_prime(n) ? n : 0); });
  std::cout << sum << std::endl;
}
