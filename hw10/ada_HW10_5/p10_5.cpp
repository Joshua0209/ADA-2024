#include "p10_5.h"
#include <bits/stdc++.h>
using namespace std;

double solve(int n, int m, vector<vector<int>> &a,
             vector<int> &b, vector<int> &c,
             vector<int> &d, vector<int> &p)
{
    vector<vector<double>> A(m, vector<double>(n + m, 0));
    vector<double> b1(m, 0), c1(n + m, 0);

    // max \sum_i (p_i x_i) - \sum_j (y_j c_j + (b_j + y_j - \sum_i (a_{i,j} x_i)) d_j)
    // y_j >= \sum_i (a_{i,j} x_i) - b_j

    // encoding
    // x0 - n-1: x_i
    // xn - n+m-1: y_j

    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            A[j][i] = a[i][j];
        }
        A[j][n + j] = -1;
    }

    for (int j = 0; j < m; ++j)
    {
        b1[j] = b[j];
    }

    for (int i = 0; i < n; ++i)
    {
        c1[i] = p[i];
        for (int j = 0; j < m; ++j)
        {
            c1[i] += a[i][j] * d[j];
        }
    }
    for (int j = 0; j < m; ++j)
    {
        c1[n + j] = -c[j] - d[j];
    }

    double C = 0;
    for (int j = 0; j < m; ++j)
    {
        C -= b[j] * d[j];
    }

    // for (int i = 0; i < A.size(); ++i)
    // {
    //     for (int j = 0; j < A[0].size(); ++j)
    //     {
    //         cout << (int)A[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for (int i = 0; i < b1.size(); ++i)
    // {
    //     cout << (int)b1[i] << " ";
    // }
    // cout << endl;
    // cout << endl;

    // for (int i = 0; i < c1.size(); ++i)
    // {
    //     cout << (int)c1[i] << " ";
    // }
    // cout << endl;
    // cout << endl;

    auto [ans, vals] = lp_solver_max(A, b1, c1);
    return ans + C;
}