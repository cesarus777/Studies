#pragma once

struct sieve_t {
	unsigned long long size;
	unsigned char *sieve;
};

int check_bit(unsigned long long x, unsigned long long n);

struct sieve_t init_sieve(unsigned long long n);

void free_sieve(struct sieve_t *s);
