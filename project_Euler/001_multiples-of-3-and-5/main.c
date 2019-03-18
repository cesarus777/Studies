#include "stdio.h"

enum { AIM = 1000 };

int main()
{
    //here cross means numbers which are multiples of 3 and 5 at the same time; in another word numbers as 15*n
    unsigned sum, sum3, num3, sum5, num5, cross_sum, cross_num;

    num3 = (AIM - 1) / 3;
    num5 = (AIM - 1) / 5;
    cross_num = (AIM - 1) / 15;

    sum3 = (num3 + 1) * num3 / 2;
    sum5 = (num5 + 1) * num5 / 2;
    cross_sum = (cross_num + 1) * cross_num / 2;

    sum = 3 * sum3 + 5 * sum5 - 15 * cross_sum;
    
    printf("%d\n", sum);
}
