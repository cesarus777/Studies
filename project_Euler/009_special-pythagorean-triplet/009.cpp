#include <iostream>

namespace {

bool is_pythagorean_triple(unsigned a, unsigned b, unsigned c) {
  return (c * c) == (a * a + b * b);
}

} // namespace

int main() {
  unsigned a, b, c;
  for (c = 0; c <= 1000; ++c)
    for (b = 0; b <= 1000; ++b)
      for (a = 0; a <= 1000; ++a)
        if ((a < b) && (b < c) && ((a + b + c) == 1000) &&
            is_pythagorean_triple(a, b, c)) {
          std::cout << a * b * c << std::endl;
          return 0;
        }
}
