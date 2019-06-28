#pragma once
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

/* this 5 defines customize build
 *   first two choose source of data for calculating
 *   next two choose algorithm of summation
 *   last one enable/disable printing generated matrix         \
 *   (if random test choosed) and matrix after rising in power
 *
 *   at the end of this file there are some conditions,        \
 *   that not allow you crack the programm
 */

#define MANUAL_INPUT
#define RANDOM_TEST
#define NAIVE_SUM
#define TRICKY_SUM
#define DEBUG_PRINT


enum { EXP = 1015, DELTA_EXP = 21, POW = 6, SIZE = 5, EPSILON = 100000 };

struct matrix_t
{
    int size;
    double *elems;
};

void print_matrix(struct matrix_t mtx);

void fill_input_matrix(struct matrix_t *mtx, int *p);

void calc_n_print_res(struct matrix_t mtx);


#ifdef MANUAL_INPUT 
#ifdef RANDOM_TEST
#undef RANDOM_TEST
#endif
#endif

#ifndef MANUAL_INPUT
#define RANDOM_TEST
#endif

#ifndef NAIVE_SUM
#ifndef TRICKY_SUM 
#define TRICKY_SUM 
#endif
#endif

#ifdef RANDOM_TEST
#include "math.h"
#include "time.h"
#endif

#ifdef TRICKY_SUM
#ifndef RANDOM_TEST
#include "math.h"
#endif
#endif

#ifdef TRICKY_SUM
#ifdef NAIVE_SUM
#define COMPARE_SUMS
#endif
#endif

