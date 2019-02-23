#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "obsha.h"

int main() {
	int n, check;
	check = scanf("%d", &n);
	assert(1 == check);

	int i, j;
	double sum_area = 0;
	struct point triangle[3];
	for(i = 0; i < n; ++i) {
		one_scanf(triangle);
		sum_area += area(triangle);
	}

	printf("%g\n", sum_area);
}
