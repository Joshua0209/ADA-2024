#include "p7_4.h"
#include <bits/stdc++.h>
#include <climits>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

vector<long long> solve(int n, int m, int k, int s,
                        vector<tuple<int, int, int>> non_negative_edges,
                        vector<tuple<int, int, int>> negative_edges)
{
  vector<long long> dis(n, LLONG_MAX);
  dis[s] = 0;

  // Adjacency list for the graph from non-negative edges
  vector<vector<pair<int, int>>> adj(n);

  for (auto &[u, v, w] : non_negative_edges)
  {
    adj[u].emplace_back(v, w);
  }

  // Dijkstra algorithm
  min_heap<pair<long long, int>> pq;
  pq.push({0, s});

  while (!pq.empty())
  {
    auto [current_dist, u] = pq.top();
    pq.pop();

    if (current_dist > dis[u])
      continue;

    for (auto &[v, weight] : adj[u])
    {
      long long new_dist = current_dist + weight;
      if (new_dist < dis[v])
      {
        dis[v] = new_dist;
        pq.push({new_dist, v});
      }
    }
  }

  // Bellman-Ford algorithm
  bool changed = true;
  while (changed)
  {
    changed = false;
    for (auto [u, v, w] : negative_edges)
    {
      if (dis[u] != LLONG_MAX && dis[v] != LLONG_MAX)
      {
        if (dis[u] + w < dis[v])
        {
          changed = true;
          dis[v] = dis[u] + w;
        }
      }
      else if (dis[u] != LLONG_MAX && dis[v] == LLONG_MAX)
      {
        changed = true;
        dis[v] = dis[u] + w;
      }
    }
  }
  bool changed = true;
  while (changed)
  {
    changed = false;
    for (auto [u, v, w] : non_negative_edges)
    {
      if (dis[u] != LLONG_MAX && dis[v] != LLONG_MAX)
      {
        if (dis[u] + w < dis[v])
        {
          changed = true;
          dis[v] = dis[u] + w;
        }
      }
      else if (dis[u] != LLONG_MAX && dis[v] == LLONG_MAX)
      {
        changed = true;
        dis[v] = dis[u] + w;
      }
    }
  }
  return dis;
}
