#include <algorithm>
#include <assert.h>
#include <cmath>
#include <concepts>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

namespace {

class sieve_t final {
  std::vector<bool> primes;
  unsigned long long largest_prime = 2;

  void calc(unsigned long long n) {
    if (n + 2 <= primes.size())
      return;

    primes = std::vector<bool>(std::sqrt(n + 1), true);
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

// Smallest Prime Factor after prev
auto spf_after(unsigned long long n, unsigned long long prev,
               const sieve_t &sieve) {
  for (auto i = prev; i <= n; i += 2)
    if (sieve.is_prime(i) && (n / i * i == n))
      return i;
  assert(false && "spf failed");
}

// Largest Prime Factor
auto lpf(unsigned long long n) {
  auto sieve = sieve_t(n);
  while (n % 2 == 0)
    n /= 2;
  unsigned long long lpf = spf_after(n, 3, sieve);
  while (n > 1) {
    lpf = spf_after(n, lpf, sieve);
    n = n / lpf;
  }
  return lpf;
}

} // namespace

int main() { std::cout << lpf(600851475143llu) << std::endl; }
