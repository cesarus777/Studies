#include <assert.h>
#include <stdio.h>
#include "obsha.h"

double area(struct point *coo)
{
    double result =
        0.5 * (coo[0].x * coo[1].y - coo[0].y * coo[1].x +
               coo[2].x * coo[0].y - coo[2].y * coo[0].x +
               coo[1].x * coo[2].y - coo[1].y * coo[2].x);
    if (result < 0)
        return (result * (-1));
    return result;
}

void one_scanf(struct point *tripointer)
{
    int k, check;
    for (k = 0; k < 3; ++k) {
        check = scanf("%lf%lf", &tripointer[k].x, &tripointer[k].y);
        assert(2 == check);
    }
}
