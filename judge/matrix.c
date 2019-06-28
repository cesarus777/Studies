#include "addition.h"

/* In addition.c you can configure this programm, depending on your needs */

struct matrix_t matrix_mult(struct matrix_t a, struct matrix_t b)
{
    assert(a.size == b.size);
    struct matrix_t res;
    res.size = a.size;
    res.elems = (double *) calloc(res.size * res.size, sizeof(double));
    assert(res.elems != NULL && a.elems != NULL && b.elems != NULL);
    for(int i = 0; i < res.size; ++i)
        for(int j = 0; j < res.size; ++j)
            for(int k = 0; k < res.size; ++k)
                res.elems[i * res.size + j] += a.elems[i * res.size + k] * b.elems[k * res.size + j];
    return res;
}

struct matrix_t matrix_pown(struct matrix_t mtx, int p)
{
    struct matrix_t prod;
    prod.size = mtx.size;
    prod.elems = (double *) calloc(prod.size * prod.size, sizeof(double));
    
    //at start prod must be unit matrix
    for(int i = 0; i < prod.size; ++i)
        prod.elems[i * prod.size + i] = 1;

    while(p > 0)
    {
        if((p % 2) == 1)
        {
            prod = matrix_mult(prod, mtx);
            p -= 1;
        } else {
            mtx = matrix_mult(mtx, mtx);
            p /= 2;
        }
    }

    return prod;
}

int
main()
{
    int size, p;
    struct matrix_t input_matrix, mul_matrix;

    fill_input_matrix(&input_matrix, &p);

    size = input_matrix.size;
    mul_matrix.size = size;
    mul_matrix.elems = calloc(size * size, sizeof(double));
    assert(mul_matrix.elems != NULL);
    mul_matrix = matrix_pown(input_matrix, p);

#ifdef DEBUG_PRINT
    print_matrix(mul_matrix);
#endif

    calc_n_print_res(mul_matrix);
    
    free(input_matrix.elems);
    free(mul_matrix.elems);
}
