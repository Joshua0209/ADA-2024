#include "p5_4.h"
#include <vector>
#include <queue>

std::vector<int> assign_states(int n, int m, std::vector<int> &u, std::vector<int> &v)
{
    std::vector<int> state(n, -1);
    std::queue<int> queue;
    state[u[0]] = 0;
    state[v[0]] = 1;
    for (int i = 1; i < m; i++)
    {
        if (state[u[i]] != -1 && state[v[i]] == -1)
        {
            state[v[i]] = 1 - state[u[i]];
        }
        else if (state[u[i]] == -1 && state[v[i]] != -1)
        {
            state[u[i]] = 1 - state[v[i]];
        }
        else if (state[u[i]] == -1 && state[v[i]] == -1)
        {
            queue.push(i);
        }
    }

    while (!queue.empty())
    {
        int no_changed_time = 0;
        while (!queue.empty() && queue.size() != no_changed_time)
        {
            int i = queue.front();
            queue.pop();
            if (state[u[i]] != -1 && state[v[i]] == -1)
            {
                state[v[i]] = 1 - state[u[i]];
                no_changed_time = 0;
            }
            else if (state[u[i]] == -1 && state[v[i]] != -1)
            {
                state[u[i]] = 1 - state[v[i]];
                no_changed_time = 0;
            }
            else if (state[u[i]] == -1 && state[v[i]] == -1)
            {
                queue.push(i);
                no_changed_time++;
            }
        }
        if (!queue.empty())
        {
            int front = queue.front();
            queue.pop();
            state[u[front]] = 0;
            state[v[front]] = 1;
        }
    }
    return state;
}
