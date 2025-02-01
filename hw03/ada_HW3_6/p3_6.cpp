#include "p3_6.h"
#include <bits/stdc++.h>
using namespace std;

pair<int, vector<int>> solve(int n, int m, vector<pair<int, int>> es) {
  vector<int> order(n);
  iota(begin(order), end(order), 1);
  return make_pair(0, order);
}
