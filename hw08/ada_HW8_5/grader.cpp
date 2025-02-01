#include "p8_5.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges)
      cin >> u >> v;

    vector<pair<int, int>> ans = solve(n, edges);
    cout << ans.size() << '\n';
    for (const auto& [u, v] : ans)
      cout << u << ' ' << v << '\n';
  }
  return 0;
}
