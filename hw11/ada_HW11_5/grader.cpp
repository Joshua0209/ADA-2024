#include "p11_5.h"
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

    auto spanning_tree = solve(n, edges);
    cout << spanning_tree.size() << '\n';
    for (auto [u, v] : spanning_tree)
      cout << u << ' ' << v << '\n';
  }
  return 0;
}
