#include "p4_4.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

int maximum_dishes(std::vector<int> &dishes, int A, int B, long long T)
{

    std::vector<long long> dp(dishes.size() + 1, LLONG_MAX);
    std::vector<std::vector<bool>> last_dishes(dishes.size() + 1, std::vector<bool>(dishes.size(), false));
    dp[0] = 0;
    for (int i = 0; i < dishes.size(); i++)
    {
        for (int k = i + 1; k > 0; k--)
        {
            long long t = last_dishes[k - 1][dishes[i]] ? A : A + B;
            if (dp[k] != LLONG_MAX && dp[k - 1] != LLONG_MAX)
            {
                if (dp[k - 1] + t < dp[k])
                {
                    dp[k] = dp[k - 1] + t;
                    last_dishes[k] = std::vector<bool>(dishes.size(), false);
                    last_dishes[k][dishes[i]] = true;
                }
                else if (dp[k - 1] + t == dp[k])
                {
                    last_dishes[k][dishes[i]] = true;
                }
            }
            else
            {
                if (dp[k - 1] != LLONG_MAX)
                {
                    dp[k] = dp[k - 1] + t;
                    last_dishes[k][dishes[i]] = true;
                }
            }
        }
    }

    int l = 0, r = dp.size() - 1;
    int best;
    while (l <= r)
    {
        int i = (l + r) / 2;
        if (dp[i] <= T + B)
        {
            best = i;
            l = i + 1;
        }
        else if (dp[i] > T + B)
        {
            r = i - 1;
        }
    }
    return best;
}
