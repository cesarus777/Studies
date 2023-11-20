#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

#ifdef NAIVE

namespace {

using factorization_t = std::unordered_map<unsigned, unsigned>;

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

  factorization_t prime_factorization(unsigned long long n) const {
    factorization_t res;
    for (auto i : std::views::iota(2u, n + 1)) {
      if (is_prime(i)) {
        while (0 == n % i) {
          n /= i;
          if (res.contains(i))
            ++res[i];
          else
            res[i] = 1;
        }
      }
    }
    return res;
  }
};

factorization_t
merge_factorization(const std::vector<factorization_t> &factorizations) {
  factorization_t merged;
  for (auto &f : factorizations) {
    for (auto [factor, pow] : f) {
      auto pos = merged.find(factor);
      if (pos == merged.end()) {
        merged[factor] = pow;
        continue;
      }
      if (pos->second < pow) {
        pos->second = pow;
        continue;
      }
    }
  }
  return merged;
}

template <std::integral i_t> i_t powi(i_t base, i_t exp) {
  double max = std::numeric_limits<i_t>::max();
  double result = std::round(std::pow(base, exp));
  return result >= max ? max : result;
}

unsigned long long
lcm_from_factorization(const factorization_t &factorization) {
  return std::accumulate(factorization.begin(), factorization.end(), 1llu,
                         [](auto acc, auto &elem) {
                           return acc * std::pow(elem.first, elem.second);
                         });
}

unsigned long long lcm_for_range(unsigned n) {
  sieve_t sieve(n);
  auto &&R =
      std::views::iota(2u, n) | std::views::transform([&sieve](auto num) {
        auto &&f = sieve.prime_factorization(num);
        return f;
      });
  std::vector<factorization_t> factorizations(R.begin(), R.end());
  auto common_factorization = merge_factorization(factorizations);
  return lcm_from_factorization(common_factorization);
}

} // namespace

int main() { std::cout << lcm_for_range(20) << std::endl; }

#else

int main() {
  int lcm = 1;
  for (int i = 2; i <= 20; ++i)
    lcm = std::lcm(lcm, i);
  std::cout << lcm << std::endl;
}

#endif
