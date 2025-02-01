#include "p9_4.h"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

std::vector<std::vector<int>> capacity;
std::vector<std::vector<int>> adj;
std::vector<int> parent;

int bfs(int source, int sink)
{
    std::fill(parent.begin(), parent.end(), -1);
    parent[source] = -2; // Mark the source as visited
    std::queue<std::pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur])
        {
            if (parent[next] == -1 && capacity[cur][next] > 0)
            {
                parent[next] = cur;
                int new_flow = std::min(flow, capacity[cur][next]);
                if (next == sink)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
};

int Maximum_Flow(int n, std::vector<std::pair<int, int>> &edges, std::vector<int> capv, std::vector<int> cape)
{
    // Build capacity matrix and adjacency list
    capacity.resize(n * 2 - 2, std::vector<int>(n * 2 - 2, 0));
    adj.resize(n * 2 - 2);

    // 0 is source, odd (2i-1) is in, even (2i) is out, 2n-3 is sink
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (edges[i].first == n || edges[i].second == 1)
        {
            continue;
        }
        int u = 2 * (edges[i].first - 1), v = 2 * (edges[i].second - 1) - 1;
        capacity[u][v] += cape[i];
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for the residual graph
    }

    for (size_t i = 0; i < capv.size(); ++i)
    {
        int u = 2 * (i + 1) - 1, v = 2 * (i + 1);
        capacity[u][v] += capv[i];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int source = 0;
    int sink = 2 * n - 3;
    int max_flow = 0;
    parent.resize(2 * n - 2);

    int new_flow;
    while ((new_flow = bfs(source, sink)) != 0)
    {
        max_flow += new_flow;

        int cur = sink;
        while (cur != source)
        {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return max_flow;
}
