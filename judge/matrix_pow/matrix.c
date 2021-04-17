#include "assert.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct matrix_t
{
    int size;
    double *elems;
};

void pm(struct matrix_t m)
{
    for(int i = 0; i < m.size; ++i)
    {
        for(int j = 0; j < m.size; ++j)
            printf(" %lf", m.elems[i * m.size + j]);
        printf("\n");
    }
}

int comp(const void *a, const void *b)
{
    double x = *(double *) a;
    double y = *(double *) b;
    if(fabs(x - y) < (0.00001))
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

void matrix_mult(struct matrix_t a, struct matrix_t b, struct matrix_t c)
{
    assert((a.size == b.size) && (b.size == c.size));
    assert(a.elems != NULL && b.elems != NULL && c.elems != NULL);
    int size = a.size;
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
        {
            a.elems[i * size + j] = 0;
            for(int k = 0; k < size; ++k)
                a.elems[i * size + j] += b.elems[i * size + k] * c.elems[j * size + k];
        }
}

void matrix_transposition(struct matrix_t a, struct matrix_t a_t)
{
    assert(a.size == a_t.size);
    assert((a.elems != NULL) && (a_t.elems != NULL));
    for(int i = 0; i < a.size; ++i)
    {
        for(int j = 0; j < a.size; ++j)
        {
            a_t.elems[j * a.size + i] = a.elems[i * a.size + j];
        }
    }
}

void matrix_pown(struct matrix_t in_mtx, struct matrix_t out_mtx, struct matrix_t tmp_mtx, int p)
{
    assert((in_mtx.size == out_mtx.size) && (out_mtx.size == tmp_mtx.size));
    assert((in_mtx.elems != NULL) && (out_mtx.elems != NULL) && (tmp_mtx.elems != NULL));
    struct matrix_t mid_res;
    int size = in_mtx.size;
    mid_res.size = size;
    mid_res.elems = (double *) calloc(size * size, sizeof(double));
   
    //at start prod must be unit matrix
    for(int i = 0; i < size; ++i)
        out_mtx.elems[i * size + i] = 1;

    while(p > 0)
    {
        if((p % 2) == 1)
        {
            matrix_transposition(in_mtx, tmp_mtx);
            matrix_mult(mid_res, out_mtx, tmp_mtx);
            memcpy(out_mtx.elems, mid_res.elems, size * size * sizeof(double));
            p -= 1;
        } else {
            matrix_transposition(out_mtx, tmp_mtx);
            matrix_mult(mid_res, out_mtx, tmp_mtx);
            memcpy(out_mtx.elems, mid_res.elems, size * size * sizeof(double));
            p /= 2;
        }
    }

    free(mid_res.elems);
}

void fill_input_matrix(struct matrix_t *input_matrix, int *p)
{
    int size; 
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
}

void calc_n_print_res(struct matrix_t mtx)
{

    double res;

    //pm(mtx);
 
    res = mtx_sum(mtx);

    printf("%lf\n", res);

}

int
main()
{
    int size, p;
    struct matrix_t input_matrix, mul_matrix, trans;

    fill_input_matrix(&input_matrix, &p);

    size = input_matrix.size;
    mul_matrix.size = size;
    trans.size = size;
    mul_matrix.elems = calloc(size * size, sizeof(double));
    trans.elems = calloc(size * size, sizeof(double));
    assert((mul_matrix.elems != NULL) && (trans.elems != NULL));
    matrix_pown(input_matrix, mul_matrix, trans, p);
    free(trans.elems);

    calc_n_print_res(mul_matrix);
    
    free(input_matrix.elems);
    free(mul_matrix.elems);
}
