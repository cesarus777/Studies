#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------
// FIBONACCI NIM by CESARUS777
// next_turn part
// verson 1.1
//------------------------------------------------------------------

// !!! NEEDS 'srand(time(NULL))' once in main before first call (optional, but desireble) !!! 

//initialization of array with fibonacci nums
unsigned long long fibs[92] = { 1, 2, 0 };

//initialization memory variable for array 'fibs'
unsigned fmem = 1;

//function for finding the biggest fibonacci number that is less than n
int fib_bin_search(unsigned long long n)
{
    int l = 0, r = fmem - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if ((fibs[m] <= n) && (fibs[m + 1] > n))
            return m;
        if ((fibs[m] < n) && (fibs[m + 1] <= n))
            l = m + 1;
        if (fibs[m] > n)
            r = m - 1;
    }
    return fmem;
}

//comparator for bsearch
int fcompar(const void *key, const void *elem)
{
    unsigned long long *n = (unsigned long long *) key;
    unsigned long long *f = (unsigned long long *) elem;

    if ((*f <= *n) && (*(f + 1) > *n))
        return 0;
    if ((*f < *n) && (*(f + 1) <= *n))
        return -1;
    if (*f > *n)
        return 1;
}

//function that returns smallest fibonacci number in its Zecondorf representation; it is important because optimal strategy is 'amount of removing objects' = 'sfnum of remaining objects'
unsigned long long sfnum(unsigned long long n)
{

    //input check
    assert(n >= 0);

    if (n < 2)
        return n;

    //finding highest fibonacci number less then n
    int i, m;

    //if we don't need to add some fibonacci numbers in the array
    if (fibs[fmem] > n) {
        m = fib_bin_search(n);

    } else {

        //if we need to add some fibonacci numbers in the array
        for (i = 2;; ++i) {
            fibs[i] = fibs[i - 1] + fibs[i - 2];
            if (fibs[i] > n) {
                m = i - 1;
                fmem = i;
                break;
            }
        }
    }

    //finishing by finding the least fibonacci number in n's Zecendorf representation
    while (n > 0) {
        n -= fibs[m];

        if (n == 0)
            return fibs[m];

        for (i = m;; --i) {
            if (fibs[i] <= n) {
                m = i;
                break;
            }
        }
    }

    //error return
    return 0;

}

//function for computer's next turn; n is amount of remaining objects, k is amount of objects gotten on the last turn 
unsigned long long next_turn(unsigned long long n, unsigned long long k)
{
    if (n <= 2 * k)
        return n;

    unsigned long long res = sfnum(n);

    assert(res);

    //rule check; if position is losing for computer, it calls luck
    if (res > 2 * k)
        res = (rand() % (2 * k - 1)) + 1;

    //prevention of fast ending
    if (3 * res > n)
        res = (rand() % n) / 3 + 1;

    return res;
}

int main()
{
    sfnum(4000);
    unsigned long long a = 3000;
    int f, *b;
    f = fib_bin_search(a);
    b = (int *) bsearch(&a, fibs, fmem, sizeof(unsigned long long),
                        fcompar);
    assert(f == b);
}
