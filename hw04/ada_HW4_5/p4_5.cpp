#include "p4_5.h"
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<long long> count_sets(int n, long long k, int L, int R, std::vector<int> c)
{
    std::vector<long long> ans(n, 45510);
    std::vector<std::vector<long long>> prefix_dp(n + 1, std::vector<long long>(R + 1, 0));
    std::vector<std::vector<long long>> suffix_dp(n + 1, std::vector<long long>(R + 1, 0));

    prefix_dp[0][0] = 1;
    suffix_dp[n][0] = 1;
    for (int i = 1; i < n; ++i)
    {
        prefix_dp[i] = prefix_dp[i - 1];
        for (int cal = R; cal >= c[i - 1]; --cal)
        {
            prefix_dp[i][cal] += prefix_dp[i - 1][cal - c[i - 1]];
            if (prefix_dp[i][cal] > k)
            {
                prefix_dp[i][cal] = k;
            }
        }
    }
    for (int i = n - 1; i >= 0; --i)
    {
        suffix_dp[i] = suffix_dp[i + 1];
        for (int cal = R; cal >= c[i]; --cal)
        {
            suffix_dp[i][cal] += suffix_dp[i + 1][cal - c[i]];
            if (suffix_dp[i][cal] > k)
            {
                suffix_dp[i][cal] = k;
            }
        }
    }

    for (int removed = 0; removed < n; ++removed)
    {
        // L-x to R-x
        std::vector<long long> suffix_sum(R + 1, 0);
        suffix_sum[R] = 1;
        for (int x = R - 1; x >= L; --x)
        {
            suffix_sum[x] = suffix_sum[x + 1] + suffix_dp[removed + 1][R - x];
        }
        for (int x = L - 1; x >= 0; --x)
        {
            suffix_sum[x] = suffix_sum[x + 1] + suffix_dp[removed + 1][R - x] - suffix_dp[removed + 1][L - x - 1];
        }

        long long count = 0;
        for (int x = 0; x <= R; ++x)
        {
            count += prefix_dp[removed][x] * suffix_sum[x];
            if (count > k)
            {
                count = k;
                break;
            }
        }
        ans[removed] = count;
    }
    return ans;
}