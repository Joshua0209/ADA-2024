#include "p3_6.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> es(m);
    for (auto &[u, v] : es)
      cin >> u >> v;
    auto [cost, ans] = solve(n, m, es);
    assert((int) ans.size() == n);
    cout << cost << ' ';
    for (int i = 0; i < n; ++i)
      cout << ans[i] << " \n"[i == n - 1];
  }
}
