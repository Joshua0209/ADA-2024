#include <bits/stdc++.h>
using namespace std;

// BFS for building level graph
bool bfs(int s, int t, vector<vector<bool>>& capacity, vector<vector<int>>& adj, vector<int>& level) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (level[v] == -1 && capacity[u][v]) { // Unvisited and residual capacity > 0
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1; // Return true if sink is reachable
}

// DFS for sending flow along augmenting paths
int dfs(int u, int t, bool flow, vector<vector<bool>>& capacity, vector<vector<int>>& adj, vector<int>& level, vector<int>& ptr) {
    if (u == t) return flow; // Reached sink

    for (int& i = ptr[u]; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (level[v] == level[u] + 1 && capacity[u][v]) {
            int bottleneck = dfs(v, t, ((flow ^ capacity[u][v]) | (flow && capacity[u][v])), capacity, adj, level, ptr);
            if (bottleneck) {
                capacity[u][v] = false;
                capacity[v][u] = true;
                return bottleneck;
            }
        }
    }
    return 0;
}

// Dinitz's Maximum Flow Algorithm
int Maximum_Flow(int n, vector<pair<int, int>>& graph, int bottleneck_idx) {
    int num_vertices = 2 * n + 2; // Nodes 0 to 2n+1
    vector<vector<bool>> capacity(num_vertices, vector<bool>(num_vertices, false));
    vector<vector<int>> adj(num_vertices);

    // Build capacity and adjacency list
    for (int i = 0; i <= 2 * n + bottleneck_idx; i++) {
        int u = graph[i].first;
        int v = graph[i].second;
        capacity[u][v] = 1; // Unit capacity
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
    }

    int total_flow = 0;
    vector<int> level(num_vertices);

    while (bfs(0, 2 * n + 1, capacity, adj, level)) {
        vector<int> ptr(num_vertices, 0);
        while (int flow = dfs(0, 2 * n + 1, INT_MAX, capacity, adj, level, ptr)) {
            total_flow += flow;
        }
    }

    // Count unmatched nodes in the first set
    int unmatched_count = 0;
    for (int i = 1; i <= n; i++) {
        bool matched = false;
        for (int j : adj[i]) {
            if (capacity[i][j] == 0 && j > n && j <= 2 * n) { // Match exists
                matched = true;
                break;
            }
        }
        if (!matched) unmatched_count++;
    }

    return unmatched_count;
}

// Graph builder function
vector<pair<int, int>> buildGraph(int n, vector<tuple<int, int, int>>& edges) {
    vector<pair<int, int>> graph;

    for (int i = 1; i <= n; i++) {
        graph.emplace_back(0, i);         // Source to left set
        graph.emplace_back(i + n, 2 * n + 1); // Right set to sink
    }

    for (const auto& e : edges) {
        int u = get<0>(e);
        int v = get<1>(e);
        graph.emplace_back(u, v + n);
    }

    return graph;
}

// Main solver with binary search over bottleneck weights
int solve(int n, int m, int t, vector<tuple<int, int, int>> edges) {
    if (n == t) return 0; // Special case: All paths match perfectly

    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b); // Sort edges by weight
    });

    auto graph = buildGraph(n, edges);
    int left = 0, right = edges.size() - 1, result = -1;

    // Binary search for the smallest bottleneck weight
    while (left <= right) {
        int mid = (left + right) / 2;
        int bottleneck = get<2>(edges[mid]);

        int num_paths = Maximum_Flow(n, graph, mid);

        if (num_paths <= t) {
            result = bottleneck;
            right = mid - 1; // Try smaller bottleneck
        } else {
            left = mid + 1; // Try larger bottleneck
        }
    }

    return result;
}
