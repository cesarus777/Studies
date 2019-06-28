#include "addition.h"

void print_matrix(struct matrix_t mtx)
{
    for(int i = 0; i < mtx.size; ++i)
    {
        for(int j = 0; j < mtx.size; ++j)
        {
          printf(" %30lf", mtx.elems[i * mtx.size + j]);
        }

        printf("\n");
    }
    printf("\n");
}

unsigned long long as_ull(double x)
{
    return *(unsigned long long *) &x;
}

double as_double(unsigned long long x)
{
    return *(double *) &x;
}

#ifdef TRICKY_SUM
int comp(const void *a, const void *b)
{
    double x = *(double *) a;
    double y = *(double *) b;
    if(fabs(x - y) < (1 / EPSILON))
        return 0;
    if(x > y)
        return 1;
    return -1;
}

double mtx_sum(struct matrix_t mtx)
{
    qsort(mtx.elems, mtx.size * mtx.size, sizeof(double), &comp);
    double res = 0;
    for(int i = 0; i < mtx.size; ++i)
        for(int j = 0; j < mtx.size; ++j)
            res += mtx.elems[i * mtx.size + j];
    return res;
}
#endif 

#ifdef NAIVE_SUM
double n_mtx_sum(struct matrix_t mtx)
{
    double res = 0;
    for(int i = 0; i < mtx.size; ++i)
        for(int j = 0; j < mtx.size; ++j)
            res += mtx.elems[i * mtx.size + j];
    return res;
}
#endif 

#ifdef RANDOM_TEST 
float gen_float (unsigned exp)
{
    unsigned res_u = (0u << 31) | ((exp & 0xff) << 23);
    unsigned mant = (unsigned) rand();
    mant &= 0x7fffff;
    res_u |= mant;
    float res = *(float *) &res_u;
    return res;
}

double gen_double (unsigned long long exp)
{
    unsigned long long sign = (unsigned long long) rand();
    sign %= 2;
    exp &= 0x7ff;
    unsigned long long res_ull = (0ull << 63) | (exp << 52);
    int x = rand();
    int y = rand();
    unsigned xu = *(unsigned *) &x;
    unsigned long long yu = *(unsigned long long *) &y;
    yu = (yu << 32) | xu;
    yu &= 0x0fffffffffffff;
    res_ull |= yu;
    double res = as_double(res_ull);
    if(isnan(res) || isinf(res))
        return 0;
    return res;
}

unsigned long long gen_exp(void)
{
    unsigned long long exp = (unsigned long long) rand();
    exp &= 0x07ff;
    while((exp < EXP - DELTA_EXP) || (exp > EXP + DELTA_EXP))
    {
        exp = (unsigned long long) rand();
        exp &= 0x07ff;
    }
    return exp;
}
#endif

void fill_input_matrix(struct matrix_t *input_matrix, int *p)
{
    int size;

#ifdef MANUAL_INPUT 
    int check = scanf("%d", p);
    assert(check == 1);
    check = scanf("%d", &size);
    assert(check == 1);
    input_matrix->size = size;
    input_matrix->elems = calloc(size * size, sizeof(double));
    assert(input_matrix->elems != NULL);
    double x;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            check = scanf("%lf", &x);
            assert(check == 1);
            input_matrix->elems[i * size + j] = x;
        }
    }
#endif

#ifdef RANDOM_TEST
    srand(time(NULL));
    *p = rand() % POW + 1;
    size = rand() % SIZE + 2;
    input_matrix->size = size;
    input_matrix->elems = calloc(size * size, sizeof(double));
    assert(input_matrix->elems != NULL);
    unsigned long long exp;
    for(int i = 0; i < size * size; ++i)
    {
        exp = gen_exp();
        input_matrix->elems[i] = gen_double(exp);
    }
#ifdef DEBUG_PRINT
    printf("p = %d, size = %d, matrix:\n", *p, size);
    print_matrix(*input_matrix);
#endif
#endif
}

void calc_n_print_res(struct matrix_t mtx)
{

    double res;

#ifdef NAIVE_SUM 
    res = n_mtx_sum(mtx);
#endif

#ifdef COMPARE_SUMS
    double n_res = res;
    printf("naive sum = %lf\n", res);
#endif 

#ifdef TRICKY_SUM 
    res = mtx_sum(mtx);
#endif

#ifdef COMPARE_SUMS
    printf("tricky sum = %lf\n", res);
    printf("difference = %lf\n", res - n_res);
#endif

#ifndef COMPARE_SUMS 
    printf("Sum is %lf\n", res);
#endif

}
