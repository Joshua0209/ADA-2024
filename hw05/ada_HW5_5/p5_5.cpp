#include "p5_5.h"
#include <vector>
#include <iostream>
#include <algorithm>

bool findEulerianCircuit(int u, std::vector<std::pair<int, int>> &edges, std::vector<bool> visited_edges, std::vector<int> &ans)
{
    int flag = false;
    int visiting_edge = -1;
    for (int j = 1; j < edges.size(); j++)
    {
        if (!visited_edges[j] && (u == edges[j].first || u == edges[j].second))
        {
            visited_edges[j] = true;
            int next_vertex = u == edges[j].second ? edges[j].first : edges[j].second;
            if (findEulerianCircuit(next_vertex, edges, visited_edges, ans))
            {
                flag = true;
                visiting_edge = j + 1;
                break;
            }
            else
            {
                visited_edges[j] = false;
            }
        }
    }
    if (!flag)
    {
        for (int j = 1; j < edges.size(); j++)
        {
            if (!visited_edges[j])
            {
                ans.clear();
                return false;
            }
        }
    }
    ans.push_back(visiting_edge);
    return true;
}

std::vector<int> Eulerian_circuit(int n, std::vector<std::pair<int, int>> &edges)
{
    std::vector<int> ans1;
    std::vector<int> ans2;
    std::vector<bool> visited_edges(edges.size(), false);
    visited_edges[0] = true;
    findEulerianCircuit(edges[0].first, edges, visited_edges, ans1);
    ans1.push_back(1);
    std::reverse(ans1.begin(), ans1.end());
    ans1.pop_back();
    findEulerianCircuit(edges[0].second, edges, visited_edges, ans2);
    ans2.push_back(1);
    std::reverse(ans2.begin(), ans2.end());
    ans2.pop_back();

    for (int i = 0; i < ans1.size(); i++)
    {
        if (ans1[i] < ans2[i])
        {
            return ans1;
        }
        else if (ans1[i] > ans2[1])
        {
            return ans2;
        }
    }
}
