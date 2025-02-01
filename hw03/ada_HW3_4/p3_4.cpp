#include "p3_4.h"
#include <vector>

std::vector<std::vector<int>> memo;
int LS = 1;

void check_square(int i, int j, std::vector<std::vector<int>> &c)
{
    if (c[i][j] == c[i - 1][j] && c[i][j] == c[i][j - 1] && c[i][j] == c[i - 1][j - 1])
    {
        memo[i][j] = std::min(std::min(memo[i - 1][j - 1], memo[i][j - 1]), memo[i - 1][j]) + 1;
        if (LS < memo[i][j])
        {
            LS = memo[i][j];
        }
    }
    else
    {
        memo[i][j] = 1;
    }
}

int largest_square(int M, int N, std::vector<std::vector<int>> &c)
{
    memo.resize(M);
    for (int i = 0; i < M; i++)
    {
        memo[i].resize(N);
    }
    for (int i = 0; i < M; i++)
    {
        memo[i][0] = 1;
    }
    for (int j = 0; j < N; j++)
    {
        memo[0][j] = 1;
    }
    int min_MN = std::min(M, N), max_MN = std::max(M, N);
    for (int i = 1; i < min_MN; i++)
    {
        check_square(i, i, c);
        for (int j = i + 1; j < max_MN; j++)
        {
            if (i < M && j < N)
            {
                check_square(i, j, c);
            }
            if (j < M && i < N)
            {
                check_square(j, i, c);
            }
        }
    }
    return LS;
}
