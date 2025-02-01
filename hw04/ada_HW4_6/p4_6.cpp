#include "p4_6.h"
#include <bits/stdc++.h>
#include <vector>
#include <iostream>

int mod = 998244353;
int m, n;
std::vector<std::vector<std::vector<int>>> dp;

int decide_next_state(int current_row, int col, std::vector<std::vector<bool>> &new_column_state)
{
    int new_row, new_col;
    if (current_row + 1 < new_column_state[0].size())
    {
        new_row = current_row + 1;
        new_col = col;
    }
    else
    {
        new_row = 0;
        new_col = col + 1;
        new_column_state[0] = new_column_state[1];
        std::fill(new_column_state[1].begin(), new_column_state[1].end(), true);
    }
    while (new_row < new_column_state[0].size() && !new_column_state[0][new_row])
    {
        new_row++;
    }
    if (new_row == new_column_state[0].size())
    {
        new_row = 0;
        new_col++;
        new_column_state[0] = new_column_state[1];
        std::fill(new_column_state[1].begin(), new_column_state[1].end(), true);
    }

    return new_col;
}

int solve_k(std::vector<std::vector<int>> &a, int k, int col, std::vector<std::vector<bool>> &column_state)
{
    // dpstate: number of dominoes left: m*n/2+1, current_column: max(m,n), column_state: 2^{2*min(m,n)}, true means valid
    if (k == 0)
    {
        return 1;
    }
    if (col >= n)
    {
        return 0;
    }
    int state = 0;
    for (int i = 0; i < column_state.size(); i++)
    {
        for (int j = 0; j < column_state[i].size(); j++)
        {
            if (column_state[i][j])
            {
                state += 1 << (j + i * column_state[i].size());
            }
        }
    }
    if (dp[k][col][state] != -1)
    {
        return dp[k][col][state];
    }
    // The column state must be non-all-zero for the first column
    int current_row = 0;
    while (!column_state[0][current_row])
    {
        current_row++;
    }
    int put_ver = 0, put_hor = 0, put_empty = 0;
    if (current_row + 1 < column_state[0].size() && column_state[0][current_row + 1] && a[current_row][col] != a[current_row + 1][col])
    {
        std::vector<std::vector<bool>> new_column_state = column_state;
        new_column_state[0][current_row] = false;
        new_column_state[0][current_row + 1] = false;
        int new_col = decide_next_state(current_row, col, new_column_state);
        put_ver = solve_k(a, k - 1, new_col, new_column_state);
    }
    if (col + 1 < n && column_state[1][current_row] && a[current_row][col] != a[current_row][col + 1])
    {
        std::vector<std::vector<bool>> new_column_state = column_state;
        new_column_state[0][current_row] = false;
        new_column_state[1][current_row] = false;
        int new_col = decide_next_state(current_row, col, new_column_state);
        put_hor = solve_k(a, k - 1, new_col, new_column_state);
    }
    if (true)
    {
        std::vector<std::vector<bool>> new_column_state = column_state;
        new_column_state[0][current_row] = false;
        int new_col = decide_next_state(current_row, col, new_column_state);
        put_empty = solve_k(a, k, new_col, new_column_state);
    }

    return dp[k][col][state] = ((put_ver + put_hor) % mod + put_empty) % mod;
}

std::vector<int> solve(int m, int n, std::vector<std::vector<int>> a)
{
    if (m > n)
    {
        std::vector<std::vector<int>> transposed_a(n, std::vector<int>(m));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                transposed_a[j][i] = a[i][j];
            }
        }
        a = transposed_a;
        std::swap(m, n);
    }
    ::m = m;
    ::n = n;
    dp.resize(m * n / 2 + 1);
    for (int i = 0; i < dp.size(); i++)
    {
        dp[i].resize(n);
        for (int j = 0; j < dp[i].size(); j++)
            dp[i][j].resize(pow(2, 2 * m), -1);
    }
    std::vector<int> ans(m * n / 2 + 1, 1);
    for (int k = 1; k < m * n / 2 + 1; k++)
    {
        std::vector<std::vector<bool>> column_state(2, std::vector<bool>(m, true));
        ans[k] = solve_k(a, k, 0, column_state);
    }
    return ans;
}
