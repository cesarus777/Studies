#include "addition.h"


/* In addition.c you can configure this programm, depending on your needs */

void matrix_mult(struct matrix_t a, struct matrix_t b, struct matrix_t c)
{
    assert((a.size == b.size) && (b.size = c.size));
    assert(a.elems != NULL && b.elems != NULL && c.elems != NULL);
    int size = a.size;
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            for(int k = 0; k < size; ++k)
                a.elems[i * size + j] += b.elems[i * size + k] * c.elems[k * size + j];
}

struct matrix_t matrix_pown(struct matrix_t mtx, int p)
{
    struct matrix_t prod, mid_res;
    int size = mtx.size;
    prod.size = size;
    mid_res.size = size;
    prod.elems = (double *) calloc(size * size, sizeof(double));
    mid_res.elems = (double *) calloc(size * size, sizeof(double));
    
    //at start prod must be unit matrix
    for(int i = 0; i < prod.size; ++i)
        prod.elems[i * prod.size + i] = 1;

    while(p > 0)
    {
        if((p % 2) == 1)
        {
            matrix_mult(mid_res, prod, mtx);
            memcpy(prod.elems, mid_res.elems, size * size * sizeof(double));
            p -= 1;
        } else {
            matrix_mult(mid_res, mtx, mtx);
            memcpy(mid_res.elems, mid_res.elems, size * size * sizeof(double));
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
