#include "p7_5.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <functional>

template <class T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

std::vector<int> solve(int n, int m, int k, int s, int t,
					   std::vector<int> &u, std::vector<int> &v, std::vector<int> &w)
{
	std::vector<int> pred(n, -1);
	std::vector<int> dist(n, INT_MAX);
	dist[s] = 0;

	// Adjacency list
	std::vector<std::vector<std::pair<int, int>>> adj(n);
	for (int i = 0; i < m; i++)
	{
		adj[u[i]].emplace_back(v[i], w[i]);
		adj[v[i]].emplace_back(u[i], w[i]);
	}

	// Dijkstra algorithm
	min_heap<std::pair<int, int>> pq;
	pq.push({0, s});

	while (!pq.empty())
	{
		auto [current_dist, u] = pq.top();
		pq.pop();

		for (auto &[v, weight] : adj[u])
		{
			int new_dist = std::max(current_dist, weight);
			if (new_dist < dist[v])
			{
				dist[v] = new_dist;
				pred[v] = u;
				pq.push({new_dist, v});
			}
		}
	}

	// for (int i = 0; i < dist.size(); i++)
	// {
	// 	std::cout << dist[i] << " ";
	// }
	// std::cout << std::endl;

	std::vector<int> path;
	for (int at = pred[t]; at != s; at = pred[at])
	{
		if (at == -1)
		{
			return {};
		}
		path.push_back(at);
	}
	path.push_back(s);

	std::reverse(path.begin(), path.end());
	return path;
}
