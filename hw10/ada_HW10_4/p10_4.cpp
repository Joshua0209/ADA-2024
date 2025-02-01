#include "p10_4.h"
#include <bits/stdc++.h>
using namespace std;

double solve(int n, int m, vector<vector<int>> &a,
             vector<int> &b, vector<int> &p)
{
    vector<vector<double>> A(m, vector<double>(n));
    vector<double> b1(m), c(n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = a[j][i];

    for (int i = 0; i < m; ++i)
        b1[i] = b[i];

    for (int i = 0; i < n; ++i)
        c[i] = p[i];

    auto [ans, vals] = lp_solver_max(A, b1, c);
    return ans;
}
