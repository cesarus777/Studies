#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "algs_h.h"

#if 0
struct sieve_t {
    unsigned size;
    unsigned char *sieve;
};
#endif

void set_bit(unsigned char *x, unsigned long long n)
{
    assert(n < 8);
    *x |= (1u << n);
}

int check_bit(unsigned long long x, unsigned long long n)
{
    assert(n < 8);
    return ((x >> n) & 1);
}

struct sieve_t init_sieve(unsigned long long n)
{
    assert(n > 2);

    unsigned char *sieve =
        (unsigned char *) calloc(n / 8 + 1, sizeof(unsigned char));

    struct sieve_t res = { n, sieve };

    assert((n > 1) && (sieve != NULL));

    unsigned long long r = (unsigned long long) sqrt(n) + 1;

    res.sieve[0] = 0x3;

    for (int i = 2; i <= r; ++i) {
        if (0 == check_bit(res.sieve[i / 8], i % 8)) {
            for (int j = 2 * i; j <= n; j += i) {
                set_bit(&res.sieve[j / 8], (j % 8));
            }
        }
    }

#if 0
    for (int i = 2; i < r; ++i) {
        if (0 == res.sieve[i]);
        for (int j = 2 * i; j < n; j += i)
            res.sieve[j] = 1;
    }
#endif

    return res;
}

void free_sieve(struct sieve_t *s)
{
    free(s->sieve);
    s->sieve = 0;
    s->size = 0;
}

int is_prime(struct sieve_t s, unsigned n)
{
    assert(n / 8 < s.size);

    return (check_bit(s.sieve[n / 8], n % 8) == 1) ? 0 : 1;
}

int nth_prime(struct sieve_t s, unsigned n)
{
    int counter = 0;
    for (int i = 2; i < s.size; ++i) {
        if (check_bit(s.sieve[i / 8], i % 8) == 0) {
            ++counter;
        }
        if (counter == n) {
            return i;
        }
    }
    return -1;
}

/*
int main()
{
    struct sieve_t s = init_sieve(10000);
    assert(is_prime(s, 96) == 0);
    assert(is_prime(s, 97) == 1);
    printf("%u\n", nth_prime(s, 9999));
    free_sieve(&s);
}
*/
