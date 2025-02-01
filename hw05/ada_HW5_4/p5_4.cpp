#include "p5_4.h"
#include <vector>
#include <queue>
#include <iostream>

std::vector<int> assign_states(int n, int m, std::vector<int> &u, std::vector<int> &v)
{
    std::vector<int> state(n, -1);
    std::vector<std::vector<int>> adj(n);

    // Build the adjacency list
    for (int i = 0; i < m; i++)
    {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }

    for (int start = 0; start < n; start++)
    {
        if (state[start] == -1)
        {
            std::queue<int> queue;
            state[start] = 0;
            queue.push(start);

            while (!queue.empty())
            {
                int node = queue.front();
                queue.pop();

                for (int neighbor : adj[node])
                {
                    if (state[neighbor] == -1)
                    {
                        state[neighbor] = 1 - state[node];
                        queue.push(neighbor);
                    }
                }
            }
        }
    }

    return state;
}
