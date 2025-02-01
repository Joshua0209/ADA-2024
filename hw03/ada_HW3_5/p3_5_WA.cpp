#include "p3_5.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
struct DPState
{
    std::vector<long long> max_size, min_size;
    long long unbalancedness;
};

DPState update_unbalancedness(DPState state1, DPState state2)
{
    if (state1.unbalancedness < state2.unbalancedness)
    {
        // std::cout << ", best=" << state1.unbalancedness;
        return state1;
    }
    else if (state1.unbalancedness > state2.unbalancedness)
    {
        return state2;
    }
    else
    {
        // std::cout << ", best increase" << state1.unbalancedness;
        state1.max_size.insert(state1.max_size.end(), state2.max_size.begin(), state2.max_size.end());
        state1.min_size.insert(state1.min_size.end(), state2.min_size.begin(), state2.min_size.end());
        return state1;
    }
}

DPState update_size(DPState dpstate, long long n)
{
    long long best_unbalancedness = LLONG_MAX;
    for (int i = 0; i < dpstate.max_size.size(); i++)
    {
        dpstate.max_size[i] = std::max<long long>(dpstate.max_size[i], n);
        dpstate.min_size[i] = std::min<long long>(dpstate.min_size[i], n);
        if (dpstate.max_size[i] - dpstate.min_size[i] < best_unbalancedness)
        {
            best_unbalancedness = dpstate.max_size[i] - dpstate.min_size[i];
        }
    }
    std::vector<long long> max_size, min_size;
    for (int i = 0; i < dpstate.max_size.size(); i++)
    {
        if (dpstate.max_size[i] - dpstate.min_size[i] == best_unbalancedness)
        {
            max_size.push_back(dpstate.max_size[i]);
            min_size.push_back(dpstate.min_size[i]);
        }
    }
    dpstate.max_size = max_size;
    dpstate.min_size = min_size;
    dpstate.unbalancedness = best_unbalancedness;
    return dpstate;
}

std::vector<long long> whole_size;
std::vector<DPState> memo;

DPState min_aux(std::vector<int> &a, int n)
{
    if (memo[n].unbalancedness != -1)
    {
        return memo[n];
    }
    if (n == 0)
    {
        return memo[n] = DPState{{a[0]}, {a[0]}, 0};
    }

    DPState ans = DPState{{0}, {0}, LLONG_MAX};
    long long last_chapter_size = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        // std::cout << std::string((a.size() - n) * 2, ' ') << "n=" << n << ", i=" << i << std::endl;
        last_chapter_size += a[i + 1];
        DPState current = min_aux(a, i);
        DPState current_whole{{whole_size[i]}, {whole_size[i]}, 0}; // The original IS the whole
        current = update_size(current, last_chapter_size);
        current_whole = update_size(current_whole, last_chapter_size);
        // std::cout << std::string((a.size() - n) * 2, ' ') << "cur: max=" << current.max_size.size() << ", min=" << current.min_size.size() << ", unb=" << current.unbalancedness << std::endl;
        // std::cout << std::string((a.size() - n) * 2, ' ') << "cur: max=" << current.max_size[0] << ", min=" << current.min_size[0] << ", unb=" << current.unbalancedness << std::endl;
        // std::cout << std::string((a.size() - n) * 2, ' ') << "cur_w: max=" << current_whole.max_size[0] << ", min=" << current_whole.min_size[0] << ", unb=" << current_whole.unbalancedness << std::endl;
        // std::cout << std::string((a.size() - n) * 2, ' ') << "n=" << n << ", i=" << i;
        if (current.unbalancedness < current_whole.unbalancedness)
        {
            ans = update_unbalancedness(current, ans);
        }
        else
        {
            ans = update_unbalancedness(current_whole, ans);
        }
        // std::cout << std::endl;
    }
    return memo[n] = ans;
}

int minimum_possible_unbalancedness(std::vector<int> &a)
{
    memo.resize(a.size(), DPState{{0}, {0}, -1});
    whole_size.resize(a.size());
    long long size = 0;
    for (int i = 0; i < a.size(); i++)
    {
        size += a[i];
        whole_size[i] = size;
    }
    return min_aux(a, a.size() - 1).unbalancedness;
}
