#include "p10_6.h"

// Reference: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/Simplex.h
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define ltj(X) if(s == -1 || make_pair(X[j],N[j]) < make_pair(X[s],N[s])) s=j
struct LPSolver {
  typedef long double T;
  typedef vector<T> vd;
  typedef vector<vd> vvd;
  const T eps = 1e-10, inf = INFINITY;
    int m, n;
    vi N, B;
    vvd D;
    LPSolver(const vvd& A, const vd& b, const vd& c) :
        m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
            rep(i,0,m) rep(j,0,n) D[i][j] = A[i][j];
            rep(i,0,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
            rep(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
            N[n] = -1; D[m+1][n] = 1;
        }
    void pivot(int r, int s) {
        T *a = D[r].data(), inv = 1 / a[s];
        rep(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
            T *b = D[i].data(), inv2 = b[s] * inv;
            rep(j,0,n+2) b[j] -= a[j] * inv2;
            b[s] = a[s] * inv2;
        }
        rep(j,0,n+2) if (j != s) D[r][j] *= inv;
        rep(i,0,m+2) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }
    bool simplex(int phase) {
        int x = m + phase - 1;
        for (;;) {
            int s = -1;
            rep(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
            if (D[x][s] >= -eps) return true;
            int r = -1;
            rep(i,0,m) {
                if (D[i][s] <= eps) continue;
                if (r == -1 || make_pair(D[i][n+1] / D[i][s], B[i])
                             < make_pair(D[r][n+1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }
    T solve(vd &x) {
        int r = 0;
        rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
        if (D[r][n+1] < -eps) {
            pivot(r, n);
            if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
            rep(i,0,m) if (B[i] == -1) {
                int s = 0;
                rep(j,1,n+1) ltj(D[i]);
                pivot(i, s);
            }
        }
        bool ok = simplex(1); x = vd(n);
        rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
        return ok ? D[m][n+1] : inf;
    }
};
#undef ltj

pair<long double, vector<long double>>
lp_solver_max(const vector<vector<long double>>& A,
    const vector<long double>& b,
    const vector<long double>& c) {
  vector<long double> x(c.size());
  LPSolver solver(A, b, c);
  long double ans = solver.solve(x);
  return make_pair(ans, x);
}

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  cout << setprecision(10) << fixed;

  int T;
  cin >> T;

  while (T --> 0) {
    int n, m, l, C;
    cin >> n >> m >> l >> C;

    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> f(l, vector<int>(m));
    vector<int> c(m), d(m), g(l), h(l), p(n), q(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        cin >> a[i][j];
    for (int j = 0; j < m; ++j)
      cin >> c[j];
    for (int j = 0; j < m; ++j)
      cin >> d[j];
    for (int k = 0; k < l; ++k)
      for (int j = 0; j < m; ++j)
        cin >> f[k][j];
    for (int k = 0; k < l; ++k)
      cin >> g[k];
    for (int k = 0; k < l; ++k)
      cin >> h[k];
    for (int i = 0; i < n; ++i)
      cin >> p[i];
    for (int i = 0; i < n; ++i)
      cin >> q[i];

    double ans = max_profit_to_ratio(n, m, l, C, a, c, d, f, g, h, p, q);
    assert(ans != INFINITY and ans != -INFINITY);
    cout << ans << '\n';
  }
}
