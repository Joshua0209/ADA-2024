#include "p9_5.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) {
    int n, m, t;
    cin >> n >> m >> t;

    vector<tuple<int, int, int>> edges(m);
    for (auto &[u, v, w] : edges)
      cin >> u >> v >> w;

    cout << solve(n, m, t, edges) << '\n';
  }
}
