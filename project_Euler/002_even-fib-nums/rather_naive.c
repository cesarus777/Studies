#include "stdio.h"

enum { AIM = 4000000 };

int main() {
	unsigned long long fibs[50] = { 1, 1, 2, 0}, fsum = 0;
	int cnt = 2;

	for(; fibs[cnt] < AIM; ++cnt) {
		fibs[cnt + 1] = fibs[cnt] + fibs[cnt - 1];
	}

	for(int i = 2; i < cnt; i += 3)
		fsum += fibs[i];

	printf("sum  = %llu\n", fsum);
}
