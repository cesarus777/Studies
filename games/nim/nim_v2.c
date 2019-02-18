#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct move {
    int pile_index;
    int stones_removed;
};

//finding nim-sum (XOR amounts of elements in piles)
int nim_sum(int *piles, int n)
{
    int i, res = piles[0];
    for (i = 1; i < n; ++i) {
        res ^= piles[i];
    }
    return res;
}

//turn in winning position
struct move winning_turn(int *piles, int n, int s)
{
    assert(s);

    struct move res;

    int xor_diff, i;
    for (i = 0; i < n; ++i) {
        xor_diff = piles[i] ^ s;
        if (xor_diff < piles[i]) {
            res.pile_index = i;
            res.stones_removed = piles[i] - xor_diff;
            break;
        }
    }
    return res;
}

//turn in losing position
struct move losing_turn(int *piles, int n)
{
    struct move res;

    int max = 0, i;
    for (i = 0; i < n; ++i) {
        if (piles[i] > max) {
            max = piles[i];
            res.pile_index = i;
        }
    }

    if (piles[res.pile_index] < 3)
        res.stones_removed = 1;
    else
        res.stones_removed = rand() % (piles[res.pile_index] / 3) + 1;

    return res;
}



//making sensible turn
struct move make_turn(int *piles, int n)
{
    struct move res;

    res.pile_index = 0;
    res.stones_removed = piles[0];
    if (n == 1)
        return res;

    int i, ns = nim_sum(piles, n);

    if (ns != 0)
        return winning_turn(piles, n, ns);

    if (ns == 0)
        return losing_turn(piles, n);
}

//random player's turn
struct move rand_turn(int *piles, int n)
{
    struct move res;

    res.pile_index = rand() % n;
    while (!piles[res.pile_index])
        res.pile_index = rand() % n;

    res.stones_removed = rand() % piles[res.pile_index] + 1;

    return res;
}

//checking end of the game
void end_check(int *check, int *piles, int n)
{
    for (int i = 0; i < (n + 1); ++i) {
        if (i == n) {
            *check = 0;
            break;
        }

        if (piles[i])
            break;
    }
}

//printing array
void print_piles(int *piles, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d   %d\n", i + 1, piles[i]);
}

//making turn; index == 1 is computer's turn, index == 0 is random turn
void turn(int *piles, int n, int *check, int index)
{
    struct move t;

    if (index)
        t = make_turn(piles, n);
    else
        t = rand_turn(piles, n);

    piles[t.pile_index] -= t.stones_removed;

    end_check(check, piles, n);
}

int main()
{
    srand(time(NULL));

    int check, n, *piles, i;
    check = rand() % 2 + 1;
    n = rand() % 10 + 1;
    piles = calloc(n, sizeof(int));

    for (i = 0; i < n; ++i)
        piles[i] = rand() % 10;

    printf("n = %d; check = %d\n", n, check);
    print_piles(piles, n);

    if (check - 1) {
        turn(piles, n, &check, 0);
        if (!check)
            printf("Random wins!\n");
    }

    for (int j = 0; check; ++j) {
        turn(piles, n, &check, 1);
        if (check) {
            turn(piles, n, &check, 0);
            if (!check)
                printf("Random wins!\n");
        } else
            printf("Computer wins!\n");
    }

    free(piles);
}
