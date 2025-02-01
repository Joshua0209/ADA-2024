#include "p11_6.h"

#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  
  int subtask;
  cin >> subtask;

  int T;
  cin >> T;

  while (T --> 0) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++)
      cin >> edges[i].first >> edges[i].second;
    pair<int, vector<int>> ans = max_cut(n, edges);
    cout << ans.first << '\n';
    assert(((int) ans.second.size()) == n);
    for(int i = 0; i < n; i++)
      cout << ans.second[i] << " \n"[i + 1 == n];
  }
}
