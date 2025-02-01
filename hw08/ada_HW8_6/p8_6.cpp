#include "p8_6.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

int DFS(int startNode, std::vector<std::vector<int>> &adjList, std::vector<bool> &visited, std::unordered_set<int> &articulation_points)
{
	int node_count = 1;
	visited[startNode] = true;

	for (int neighbor : adjList[startNode])
	{
		if (!visited[neighbor] && articulation_points.find(neighbor) == articulation_points.end())
		{
			node_count += DFS(neighbor, adjList, visited, articulation_points);
		}
	}
	return node_count;
}

void find_articulation_points(int n, std::vector<std::vector<int>> &adj, std::unordered_set<int> &articulation_points)
{
	// Tarjan's Algorithm Variables
	std::vector<int> disc(n, -1);		 // Discovery times of visited vertices
	std::vector<int> low(n, -1);		 // Lowest discovery time reachable
	std::vector<bool> visited(n, false); // Visited vertices
	int time = 0;						 // Discovery time counter

	// Helper function for DFS
	auto dfs = [&](auto &&self, int u, int parent) -> void
	{
		visited[u] = true;
		disc[u] = low[u] = ++time;
		int child_count = 0;

		for (int v : adj[u])
		{
			if (!visited[v])
			{ // If v is not visited
				++child_count;
				self(self, v, u);
				low[u] = std::min(low[u], low[v]);

				// Special case for the root node
				if (parent == -1 && child_count > 1)
				{
					articulation_points.insert(u);
				}
				// Articulation point conditions
				if (parent != -1 && low[v] >= disc[u])
				{
					articulation_points.insert(u);
				}
			}
			else if (v != parent)
			{ // Back edge
				low[u] = std::min(low[u], disc[v]);
			}
		}
	};

	// Run DFS for all connected components
	std::fill(visited.begin(), visited.end(), false);
	for (int i = 0; i < n; ++i)
	{
		if (!visited[i])
		{
			dfs(dfs, i, -1);
		}
	}
}

long long solve(int n, int m, std::vector<int> &u, std::vector<int> &v)
{
	// Graph adjacency list
	std::vector<std::vector<int>> adj(n);
	for (int i = 0; i < m; ++i)
	{
		adj[u[i]].push_back(v[i]);
		adj[v[i]].push_back(u[i]);
	}

	std::unordered_set<int> articulation_points; // Articulation points set
	find_articulation_points(n, adj, articulation_points);

	if (articulation_points.size() == 0)
	{
		return 0;
	}

	std::vector<bool> visited(n, false);
	// for (int ap : articulation_points)
	// {
	// 	visited[ap] = true;
	// }

	long long ans = adj.size() * (adj.size() - 1) / 2;
	for (int i = 0; i < visited.size(); i++)
	{
		if (!visited[i] && articulation_points.find(i) == articulation_points.end())
		{
			long long node_weight = DFS(i, adj, visited, articulation_points);
			ans -= node_weight * (node_weight - 1) / 2;
		}
	}
	return ans;
}
