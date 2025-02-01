#include "p4_6.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n;
  cin >> m >> n;

  vector<vector<int>> a(m, vector<int>(n));
  for (auto &i : a) for (int &j : i) cin >> j;
  
  auto ans = solve(m, n, a);

  assert((int) ans.size() == m * n / 2 + 1);
  for (int i = 0; i <= m * n / 2; ++i)
    cout << ans[i] << " \n"[i == m * n / 2];
}
