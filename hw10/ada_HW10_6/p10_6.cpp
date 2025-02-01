#include "p10_6.h"
#include <bits/stdc++.h>
using namespace std;

double max_profit_to_ratio(int n, int m, int l, int C,
                           vector<vector<int>> &a, vector<int> &c,
                           vector<int> &d, vector<vector<int>> &f,
                           vector<int> &g, vector<int> &h,
                           vector<int> &p, vector<int> &q)
{

    // max: \sum_i (p_i x_i)
    // y_j >= \sum_i (a_{i,j} x_i) - \sum_k (f_{k,j} z_k)
    // z_k <= h_k t
    // x_i <= q_i t
    // \sum_i (\sum_j (-a_{i,j} d_j)) x_i) + \sum_j ((c_j + d_j) y_j) + \sum_k (g_k z_k) + (C+\sum_j (b_j d_j))t = 1

    // var: n + m + l + 1
    // x_i: 0   - n-1
    // y_j: n   - n+m-1
    // z_k: n+m - n+m+l-1
    // t  : n+m+l

    // constraints: m + l + n + 2
    // \sum_i (a_{i,j} x_i) - y_j + \sum_k (-f_{k,j} z_k) <= 0
    // z_k - h_k t <= 0
    // x_i - q_i t <= 0
    // \sum_i (\sum_j (-a_{i,j} d_j)) x_i) + \sum_j ((c_j + d_j) y_j) + \sum_k (g_k z_k) + (C+\sum_j (b_j d_j))t <= 1
    // \sum_i (\sum_j (a_{i,j} d_j)) x_i) + \sum_j ((-c_j - d_j) y_j) + \sum_k (-g_k z_k) + (C-\sum_j (b_j d_j))t <= -1

    vector<vector<long double>> A(2 * m + l + n + 2, vector<long double>(n + 2 * m + l + 1, 0));
    vector<long double> b1(2 * m + l + n + 2), c1(n + 2 * m + l + 1);

    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            A[j][i] = a[i][j];
        }
        A[j][n + j] = -1;
        for (int k = 0; k < l; ++k)
        {
            A[j][n + m + k] = -f[k][j];
        }
    }

    for (int k = 0; k < l; ++k)
    {
        A[m + k][n + m + k] = 1;
        A[m + k][n + m + l] = -h[k];
    }

    for (int i = 0; i < n; ++i)
    {
        A[m + l + i][i] = 1;
        A[m + l + i][n + m + l] = -q[i];
    }

    // \sum_i (\sum_j (-a_{i,j} d_j)) x_i) + \sum_j ((c_j + d_j) y_j) + \sum_k ((g_k + \sum_{j} (f_{k,j} d_j)) z_k) + Ct <= 1
    // \sum_i (\sum_j (a_{i,j} d_j)) x_i) - \sum_j ((c_j + d_j) y_j) - \sum_k ((g_k + \sum_{j} (f_{k,j} d_j)) z_k) - Ct  <= -1
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            A[m + l + n][i] -= a[i][j] * d[j];
            A[m + l + n + 1][i] += a[i][j] * d[j];
        }
    }

    for (int j = 0; j < m; ++j)
    {
        A[m + l + n][n + j] = c[j] + d[j];
        A[m + l + n + 1][n + j] = -c[j] - d[j];
    }
    for (int k = 0; k < l; ++k)
    {
        A[m + l + n][n + m + k] = g[k];
        A[m + l + n + 1][n + m + k] = -g[k];
        for (int j = 0; j < m; ++j)
        {
            A[m + l + n][n + m + k] += f[k][j] * d[j];
            A[m + l + n + 1][n + m + k] -= f[k][j] * d[j];
        }
    }
    A[m + l + n][n + m + l] = C;
    A[m + l + n + 1][n + m + l] = -C;

    // b
    b1[m + l + n] = 1;
    b1[m + l + n + 1] = -1;

    // c
    // max: \sum_i (p_ix_i)
    for (int i = 0; i < n; ++i)
    {
        c1[i] = p[i];
    }

    auto [ans, vals] = lp_solver_max(A, b1, c1);
    return ans;
}
