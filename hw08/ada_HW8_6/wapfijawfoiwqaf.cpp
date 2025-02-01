#include <vector>
#include <stack>
#include <unordered_set>
#include "p8_6.h"

void findArticulationPoints(int u, int parent, int &time, const std::vector<std::vector<int>> &adj,
                            std::vector<int> &disc, std::vector<int> &low,
                            std::unordered_set<int> &articulation_points)
{
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : adj[u])
    {
        if (disc[v] == -1)
        {
            children++;
            findArticulationPoints(v, u, time, adj, disc, low, articulation_points);
            low[u] = std::min(low[u], low[v]);

            if (parent == -1 && children > 1)
                articulation_points.insert(u);
            if (parent != -1 && low[v] >= disc[u])
                articulation_points.insert(u);
        }
        else if (v != parent)
        {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

void dfs(int u, const std::vector<std::vector<int>> &adj,
         const std::unordered_set<int> &articulation_points, std::vector<bool> &visited, long long &size)
{
    visited[u] = true;
    size++;
    for (int v : adj[u])
    {
        if (!articulation_points.count(v) && !visited[v])
        {
            dfs(v, adj, articulation_points, visited, size);
        }
    }
}

long long solve(int n, int m, std::vector<int> &u, std::vector<int> &v)
{
    // Build the adjacency list
    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < m; ++i)
    {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }

    // Find articulation points
    std::vector<int> disc(n, -1), low(n, -1);
    std::unordered_set<int> articulation_points;
    int time = 0;
    for (int i = 0; i < n; ++i)
    {
        if (disc[i] == -1)
        {
            findArticulationPoints(i, -1, time, adj, disc, low, articulation_points);
        }
    }

    // Remove articulation points and find connected components (blocks)
    std::vector<bool> visited(n, false);
    long long total_pairs_within_blocks = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!articulation_points.count(i) && !visited[i])
        {
            long long size = 0;
            dfs(i, adj, articulation_points, visited, size);
            total_pairs_within_blocks += size * (size - 1) / 2;
        }
    }

    // Total possible pairs
    long long total_pairs = (long long)n * (n - 1) / 2;

    // The result is total pairs minus pairs within blocks
    return total_pairs - total_pairs_within_blocks;
}