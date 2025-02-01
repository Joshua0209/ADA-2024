#include "p5_6.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<pair<int, int>> es(M);
  for (int i = 0; i < M; ++i)
    cin >> es[i].first >> es[i].second;

  string ans = solve(N, M, es);
  assert((int) ans.size() == N);
  cout << ans << '\n';
}
