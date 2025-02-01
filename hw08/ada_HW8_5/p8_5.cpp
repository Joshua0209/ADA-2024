#include "p8_5.h"
#include <bits/stdc++.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
using namespace std;

void dfs(int u, const vector<vector<int>> &adj, vector<bool> &visited, stack<int> &order)
{
  visited[u] = true;
  for (int v : adj[u])
    if (!visited[v])
      dfs(v, adj, visited, order);
  order.push(u);
}

void reverseDfs(int u, const vector<vector<int>> &reverseAdj, vector<bool> &visited, vector<int> &component)
{
  visited[u] = true;
  component.push_back(u);
  for (int v : reverseAdj[u])
    if (!visited[v])
      reverseDfs(v, reverseAdj, visited, component);
}

vector<pair<int, int>> solve(int n, vector<pair<int, int>> edges)
{
  vector<vector<int>> adj(n + 1), reverseAdj(n + 1);
  for (auto &e : edges)
  {
    adj[e.first].push_back(e.second);
    reverseAdj[e.second].push_back(e.first);
  }

  // Step 1: Find SCCs using Kosaraju's Algorithm
  stack<int> order;
  vector<bool> visited(n + 1, false);

  for (int i = 1; i <= n; i++)
    if (!visited[i])
      dfs(i, adj, visited, order);

  fill(visited.begin(), visited.end(), false);
  vector<vector<int>> sccs;

  while (!order.empty())
  {
    int u = order.top();
    order.pop();
    if (!visited[u])
    {
      vector<int> component;
      reverseDfs(u, reverseAdj, visited, component);
      sccs.push_back(component);
    }
  }

  // Step 2: Contract SCCs into a DAG
  vector<int> sccId(n + 1);
  for (int i = 0; i < sccs.size(); i++)
    for (int u : sccs[i])
      sccId[u] = i;

  unordered_set<int> sources, sinks;
  vector<unordered_set<int>> dag(sccs.size());
  for (auto &e : edges)
  {
    int u = sccId[e.first], v = sccId[e.second];
    if (u != v)
      dag[u].insert(v);
  }

  vector<int> inDegree(sccs.size(), 0), outDegree(sccs.size(), 0);
  for (int u = 0; u < dag.size(); u++)
  {
    for (int v : dag[u])
    {
      outDegree[u]++;
      inDegree[v]++;
    }
  }

  for (int i = 0; i < sccs.size(); i++)
  {
    if (inDegree[i] == 0)
      sources.insert(i);
    if (outDegree[i] == 0)
      sinks.insert(i);
  }

  // Step 3: Add edges to connect sources to sinks
  int numEdges = max(sources.size(), sinks.size());
  vector<pair<int, int>> newEdges;
  auto itSrc = sources.begin(), itSink = sinks.begin();
  while (itSrc != sources.end() && itSink != sinks.end())
  {
    newEdges.emplace_back(sccs[*itSink].back(), sccs[*itSrc].front());
    itSrc++;
    itSink++;
  }
  while (itSrc != sources.end())
  {
    newEdges.emplace_back(sccs[0].back(), sccs[*itSrc].front());
    itSrc++;
  }
  while (itSink != sinks.end())
  {
    newEdges.emplace_back(sccs[*itSink].back(), sccs[0].front());
    itSink++;
  }

  return newEdges;
}
