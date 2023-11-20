#include <iostream>
#include <ranges>
#include <vector>

namespace {

class sieve_t final {
  std::vector<bool> sieve;
  std::vector<unsigned long long> primes;

  void calc(unsigned long long n) {
    if (n + 2 <= sieve.size())
      return;

    sieve = std::vector<bool>(n, true);
    for (auto i : std::views::iota(0u, sieve.size())) {
      if (!sieve[i])
        continue;
      auto curr = i + 2;
      primes.push_back(curr);
      for (auto elem : sieve | std::views::drop(i) | std::views::stride(curr) |
                           std::views::drop(1))
        elem = false;
    }
  }

public:
  sieve_t(unsigned long long n) { calc(n); }

  bool is_prime(unsigned long long n) const {
    if (n <= 2)
      return true;

    if (n - 2 >= sieve.size())
      return false;
    return sieve[n - 2];
  }

  unsigned long long get_nth(unsigned n) { return primes.at(n); }
};

} // namespace

int main() {
  sieve_t sieve(200'000);
  std::cout << sieve.get_nth(10'000) << std::endl;
}
