#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

void fill_grid(char grid[9][9])
{
    int i, j, check;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            check = scanf("%c", &grid[i][j]);
            assert(check == 1);
            grid[i][j] -= '0';
        }
        scanf("%c", &check);
    }
}

void copy_grid(char cg[9][9], const char og[9][9])
{
    int i, j;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            cg[i][j] = og[i][j];
        }
    }
}

void print_grid(char g[9][9])
{
    int i, j;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j)
            printf("%d", g[i][j]);
        printf("\n");
    }
    printf("\n");
}

// checking repeat
char check_cell(char g[9][9], int a, int b)
{
    //checking lines
    int i, j;
    for (i = 0; i < 9; ++i) {
        if ((g[a][b] == g[i][b]) && (a != i))
            return 0;
        if ((g[a][b] == g[a][i]) && (b != i))
            return 0;
    }

    //checking square
    int square_shift_x = a / 3, square_shift_y = b / 3;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j)
            if ((g[a][b] == g[square_shift_x + i][square_shift_y + j])
                && ((a != square_shift_x + i) || b != square_shift_y + j))
                return 0;
    }

    return 1;

}

int main()
{
    char orig_grid[9][9];
    fill_grid(orig_grid);
    char cgrid[9][9];
    copy_grid(cgrid, orig_grid);

    print_grid(orig_grid);
    printf("\n");
    print_grid(cgrid);

    int i, j, im, ij;
    scanf("%d %d", &im, &ij);
    for (i = 0; i < im; ++i) {
        for (j = 0; j < ij; ++j) {
            if (cgrid[i][j] == 0) {
                cgrid[i][j] = 1;
                while (check_cell(cgrid, i, j) == 0)
                    ++cgrid[i][j];
                while (cgrid[i][j] == 10) {
                    cgrid[i][j] = 0;
                    --j;
                    if (j < 0) {
                        j = 8;
                        --i;
                        ++cgrid[i][j];
                        continue;
                    }

                    if (cgrid[i][j] == orig_grid[i][j]) {
                        while (cgrid[i][j] == orig_grid[i][j]) {
                            --j;
                            if (j < 0) {
                                j = 8;
                                --i;
                            }

                        }
                        ++cgrid[i][j];
                    }
                }
            }
        }
    }

    printf("\nSolving\n");
    print_grid(cgrid);

}
