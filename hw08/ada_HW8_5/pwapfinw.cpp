#include "p8_5.h"
#include <vector>
#include <bitset>
#include <array>
#include <algorithm>
#include <functional>
#include <utility> // for std::pair

using namespace std;

vector<pair<int, int>> solve(int n, vector<pair<int, int>> edges)
{
    const int t = 1000004;
    int k = 0;
    bitset<1000004> vis, F;
    array<int, 1000004> in = {0}, out = {0}, scc = {0}, S = {0};
    array<vector<int>, 1000004> G, R;
    array<vector<pair<int, int>>, 1000004> D;
    vector<int> ord, I, O, A, B;
    vector<pair<int, int>> ans;

    // BFS with explicit type for recursion
    function<void(int)> BFS = [&](int u)
    {
        if (vis[u])
            return;
        vis[u] = 1;
        for (int v : R[u])
            BFS(v);
        ord.push_back(u);
    };

    // DFS with explicit type for recursion
    function<void(int)> DFS = [&](int u)
    {
        if (scc[u])
            return;
        scc[u] = k;
        for (int v : G[u])
            DFS(v);
    };

    // Flow function with explicit type for recursion
    function<bool(int)> flow = [&](int u) -> bool
    {
        if (u == t)
            return true;
        for (auto &[v, f] : D[u])
        {
            if (f)
                continue;
            f = 1;
            if (flow(v))
            {
                if (!in[u])
                    I.push_back(u), F[u] = 1;
                if (!out[u])
                    O.push_back(u), F[u] = 1;
                return true;
            }
        }
        return false;
    };

    // Building graph
    for (auto [a, b] : edges)
    {
        G[a].push_back(b);
        R[b].push_back(a);
    }

    // Detect SCCs
    for (int i = 1; i <= n; i++)
        BFS(i);
    reverse(ord.begin(), ord.end());
    for (int u : ord)
    {
        if (!scc[u])
            k++;
        DFS(u);
    }

    // If graph is already strongly connected, no edges needed
    if (k == 1)
        return {};

    // Build condensed graph
    for (int u = 1; u <= n; u++)
    {
        S[scc[u]] = u;
        for (int v : G[u])
        {
            if (scc[v] == scc[u])
                continue;
            D[scc[u]].emplace_back(scc[v], 0);
        }
    }

    // Remove duplicate edges and calculate in/out degrees
    for (int i = 1; i <= k; i++)
    {
        sort(D[i].begin(), D[i].end());
        D[i].erase(unique(D[i].begin(), D[i].end()), D[i].end());
        for (auto [j, f] : D[i])
        {
            in[j]++;
            out[i]++;
        }
    }

    // Add virtual edges to ensure flow completion
    for (int i = 1; i <= k; i++)
    {
        if (!out[i])
            D[i].emplace_back(t, 0);
    }

    // Flow calculation for unmatched SCCs
    int a = 0, b = 0;
    for (int i = 1; i <= k; i++)
    {
        if (!in[i])
            flow(i), a = i;
        if (!out[i])
            b = i;
    }

    // Gather unmatched SCCs
    for (int i = 1; i <= k; i++)
    {
        if (F[i])
            continue;
        if (!in[i])
            A.push_back(i);
        if (!out[i])
            B.push_back(i);
    }

    // Match unmatched nodes
    for (size_t i = 0; i < I.size() - 1; i++)
    {
        ans.emplace_back(O[i], I[i + 1]);
    }
    if (!I.empty())
        ans.emplace_back(O.back(), I[0]);

    for (size_t i = 0; i < min(A.size(), B.size()); i++)
    {
        ans.emplace_back(B[i], A[i]);
    }
    if (A.size() > B.size())
    {
        for (size_t i = B.size(); i < A.size(); i++)
        {
            ans.emplace_back(b, A[i]);
        }
    }
    else
    {
        for (size_t i = A.size(); i < B.size(); i++)
        {
            ans.emplace_back(B[i], a);
        }
    }

    // Prepare the result with original node numbers
    vector<pair<int, int>> result;
    for (auto [u, v] : ans)
    {
        result.emplace_back(S[u], S[v]);
    }
    return result;
}