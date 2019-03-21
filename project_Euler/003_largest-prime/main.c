#include <math.h>
#include <stdio.h>
#include <time.h>
#include "algs_h.h"

unsigned long long spm(unsigned long long n, unsigned long long last,
                  struct sieve_t *s)
{
    for (int i = last;; ++i) {
        //if (0 != s->sieve[i / 8]) {
            if (0 == check_bit(s->sieve[i / 8], i % 8))
                if ((n / i) * i == n)
                    return i;
        //}
    }
}

unsigned long long lpm(unsigned long long n, struct sieve_t *s)
{
    unsigned long long m = 2;
    while (n > 1) {
        m = spm(n, m, s);
        n = n / m;
    }
    return m;
}

int main()
{
    unsigned long long input = 22751046341;
    unsigned long long top = sqrt(input) + 1;
    unsigned long long start_time  = time(NULL);
    struct sieve_t s = init_sieve(top);
    printf("The largest prime factor of %llu is %llu\n", input, lpm(input, &s));
    unsigned long long end_time = time(NULL);
    printf("Time is %llu\n", end_time - start_time);
    free_sieve(&s);
}
