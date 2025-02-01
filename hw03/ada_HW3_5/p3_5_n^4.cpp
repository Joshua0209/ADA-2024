#include "p3_5.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <unordered_map>
#include <algorithm>

bool split(std::vector<int> &a, long long max_value, long long min_value)
{
    std::vector<int> memo(a.size() + 1, INT_MAX);
    memo[0] = 0;
    for (int i = 1; i < a.size() + 1; i++)
    {
        long long current_sum = 0;
        for (int j = i; j > 0; j--)
        {
            current_sum += a[j - 1];
            if (current_sum >= min_value && current_sum <= max_value)
            {
                if (memo[j - 1] != INT_MAX)
                {
                    memo[i] = std::min(memo[i], memo[j - 1] + 1);
                }
            }
            else if (current_sum > max_value)
            {
                break;
            }
        }
    }
    return memo[a.size()] != INT_MAX && memo[a.size()] != 1;
}

int minimum_possible_unbalancedness(std::vector<int> &a)
{
    std::vector<long long> intervals;
    for (int i = 0; i < a.size(); i++)
    {
        long long tmp = 0;
        for (int j = i; j < a.size(); j++)
        {
            tmp += a[j];
            intervals.push_back(tmp);
        }
    }
    std::sort(intervals.begin(), intervals.end());
    std::unordered_map<long long, int> frequency;
    for (int i = intervals.size() - 1; i >= 0; i--)
    {
        if (frequency[intervals[i]] <= 1)
        {
            frequency[intervals[i]]++;
        }
        else
        {
            intervals.erase(intervals.begin() + i);
        };
    }
    int idx_max_min_value = intervals.size();
    for (int i = 0; i < intervals.size(); i++)
    {
        if (intervals[i] > intervals[intervals.size() - 1] / 2 + 1)
        {
            idx_max_min_value = i;
            break;
        }
    }
    int max_value = *max_element(a.begin(), a.end());
    int min_value = *min_element(a.begin(), a.end());
    int best_unbalancedness = max_value - min_value;
    int idx_min_max_value = 0;
    for (int i = intervals.size() - 1; i >= 0; i--)
    {
        if (intervals[i] < max_value)
        {
            idx_min_max_value = i;
            break;
        }
    }

    int left = 0;
    for (int right = idx_min_max_value; right < intervals.size(); right++) //
    {
        // std::cout << left << " " << right << " " << intervals[left] << " " << intervals[right] << std::endl;
        while (left < right && split(a, intervals[right], intervals[left]))
        {
            left++;
        }

        if (intervals[right] - intervals[left - 1] < best_unbalancedness && split(a, intervals[right], intervals[left - 1]))
        {
            best_unbalancedness = intervals[right] - intervals[left - 1];
            // std::cout << "best_unbalancedness: " << best_unbalancedness << std::endl;
        }
        if (best_unbalancedness == 0 || left > idx_max_min_value)
        {
            return best_unbalancedness;
        }
    }
    return best_unbalancedness;
}
