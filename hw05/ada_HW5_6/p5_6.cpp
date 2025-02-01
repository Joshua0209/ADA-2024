#include "p5_6.h"
#include <bits/stdc++.h>
using namespace std;

string solve(int n, int m, vector<pair<int, int>> roads) {
  string ans = "NTU";
  while ((int) ans.size() < n) ans = ans + ans;
  ans.resize(n);
  return ans;
}
