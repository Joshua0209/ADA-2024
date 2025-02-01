#include "p7_4.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<tuple<int, int, int>> non_negative_edges, negative_edges;
    for (int u, v, w, i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      assert(w >= 0);
      non_negative_edges.emplace_back(u, v, w);
    }
    for (int u, v, w, i = 0; i < k; ++i) {
      cin >> u >> v >> w;
      assert(w < 0);
      negative_edges.emplace_back(u, v, w);
    }

    vector<long long> ans = solve(n, m, k, s, non_negative_edges, negative_edges);
    for (int i = 0; i < n; ++i) {
      if (ans[i] == LLONG_MAX)
        cout << "INF";
      else
        cout << ans[i];
      cout << " \n"[i == n - 1];
    }
  }
}
