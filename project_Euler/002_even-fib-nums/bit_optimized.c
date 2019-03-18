#include "stdio.h"

enum { AIM = 4000000 };

int main() {
    unsigned long long fibs[15] = { 2, 8, 0 }, fsum = 10;

    for(int i = 2;; ++i) {
	    fibs[i] = 4 * fibs[i - 1] + fibs[i - 2];
	    if(fibs[i] > 4000000) break;
	    fsum += fibs[i];
    }

    printf("sum = %llu\n", fsum);
}
