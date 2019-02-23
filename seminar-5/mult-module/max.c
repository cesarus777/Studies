#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "obsha.h"

int main() {
	int n, check;
	check = scanf("%d", &n);
	assert(1 == check);

	int i, j;
	double tmp_area, max_area = 0;
	struct point triangle[3];
	for(i = 0; i < n; ++i) {
		one_scanf(triangle);

		tmp_area = area(triangle);

		if(max_area < tmp_area) max_area = tmp_area;
	}

	printf("%g\n", max_area);
}

