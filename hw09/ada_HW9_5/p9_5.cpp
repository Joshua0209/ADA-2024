#include "p9_5.h"
#include <bits/stdc++.h>
using namespace std;

bool bfs(int source, int sink, vector<int> &level, const vector<vector<bool>> &capacity, const vector<vector<int>> &adj)
{
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (level[v] == -1 && capacity[u][v])
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[sink] != -1; // Return whether the sink is reachable
}

// DFS to send flow in blocking flow
int dfs(int u, bool flow, int sink, vector<int> &level, vector<int> &ptr, vector<vector<bool>> &capacity, const vector<vector<int>> &adj)
{
    if (u == sink)
        return flow;

    for (int &i = ptr[u]; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (level[v] == level[u] + 1 && capacity[u][v] == 1)
        {
            int pushed = dfs(v, flow && capacity[u][v], sink, level, ptr, capacity, adj);
            if (pushed)
            {
                capacity[u][v] = 0;
                capacity[v][u] = 1;
                return pushed;
            }
        }
    }
    return 0;
}

int Maximum_Flow(int n, int source, int sink, vector<vector<bool>> &capacity, vector<vector<int>> &adj)
{
    vector<int> level(2 * n + 2);
    int max_flow = 0;

    while (bfs(source, sink, level, capacity, adj))
    {
        vector<int> ptr(2 * n + 2, 0);
        while (int flow = dfs(source, 1, sink, level, ptr, capacity, adj))
        {
            max_flow += flow;
        }
    }
    return max_flow;
}

void add_edge(int u, int v, vector<vector<bool>> &capacity, vector<vector<int>> &adj)
{
    capacity[u][v] = 1;
    adj[u].push_back(v);
    adj[v].push_back(u); // Add reverse edge for the residual graph
    return;
}

int t_solve(int n, vector<tuple<int, int, int>> edges)
{
    vector<vector<bool>> capacity(n * 2 + 2, vector<bool>(n * 2 + 2, 0));
    vector<vector<int>> adj(n * 2 + 2);

    // 0 is source, 2n+1 is sink. 2i-1 is out, 2i is in
    int src = 0, sink = 2 * n + 1;
    for (int i = 1; i < n + 1; ++i)
    {
        int out = 2 * i - 1, in = 2 * i;
        add_edge(src, out, capacity, adj);
        add_edge(in, sink, capacity, adj);
    }

    for (int i = 0; i < edges.size(); ++i)
    {
        if (get<0>(edges[i]) == get<1>(edges[i]))
        {
            continue;
        }
        int u = 2 * get<0>(edges[i]) - 1, v = 2 * get<1>(edges[i]);
        add_edge(u, v, capacity, adj);
    }

    int max_flow = Maximum_Flow(n, src, sink, capacity, adj);
    return n - max_flow;
}

int solve(int n, int m, int t, vector<tuple<int, int, int>> edges)
{
    if (n == t)
    {
        return 0;
    }
    int t_now = t_solve(n, edges);
    if (t_now > t)
    {
        return -1;
    }

    sort(edges.begin(), edges.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
         { return get<2>(a) < get<2>(b); }); // Sort by third element

    std::vector<int> weight, pos;
    int now = get<2>(edges[0]);
    for (int i = 0; i < edges.size(); ++i)
    {
        if (get<2>(edges[i]) != now)
        {
            weight.push_back(now);
            pos.push_back(i - 1);
            now = get<2>(edges[i]);
        }
    }
    weight.push_back(now);
    pos.push_back(edges.size() - 1);

    int lo = 0, hi = weight.size() - 1;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        int t_now = t_solve(n, vector<tuple<int, int, int>>(edges.begin(), edges.begin() + pos[mid] + 1));
        if (t_now > t)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }

    return weight[lo];
}