#include "p6_4.h"
#include <bits/stdc++.h>
using namespace std;

boolean_matrix boolean_matrix_multiplication(
    boolean_matrix A, boolean_matrix B) {
  int n = (int) A.size();
  boolean_matrix C(n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      C[i][j] = B[j][i];
  swap(B, C);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      C[i][j] = (A[i] & B[j]).any();
  return C;
}

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) {
    int n;
    cin >> n;

    boolean_matrix g;
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      reverse(begin(s), end(s));
      g.emplace_back(s);
    }

    boolean_matrix r = solve(n, g);
    assert((int) r.size() == n);
    for (const boolean_array &i : r) {
      string s = i.to_string();
      reverse(begin(s), end(s));
      cout << s.substr(0, n) << '\n';
    }
  }
}
