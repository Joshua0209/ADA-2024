#include "p11_5.h"
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> solve(int n, vector<pair<int, int>> edges)
{
  vector<pair<int, int>> ans;
  vector<bool> marked(n, false);
  vector<bool> incoming(n, false);
  vector<vector<int>> adj(n);
  for (auto &[u, v] : edges)
  {
    adj[u].push_back(v);
    incoming[v] = true;
  }
  int s;
  for (int i = 0; i < n; i++)
  {
    if (!incoming[i])
    {
      s = i;
      marked[s] = true;
      break;
    }
  }
  int min_out_degree = n;
  return ans;
}
