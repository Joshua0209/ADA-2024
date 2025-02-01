#include "p3_5.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <algorithm>

int minimum_possible_unbalancedness(std::vector<int> &a)
{
    std::vector<std::vector<std::vector<long long>>> dp(a.size(), std::vector<std::vector<long long>>(a.size(), std::vector<long long>(2, 0)));
    std::vector<long long> sum(a.size(), 0);
    long long size = 0;
    for (int i = 0; i < a.size(); i++)
    {
        size += a[i];
        sum[i] = size;
        dp[i][0] = {a[0], a[0]};
        dp[0][i] = {size, size};
    }

    for (int i = 1; i < dp.size(); i++)
    {
        for (int j = 1; j < dp[i].size(); j++)
        {
            // std::cout << "i=" << i << " j=" << j << " ";
            long long best = LLONG_MAX;
            long long current_sum = 0;
            for (int k = j - 1; k >= 0; k--)
            {
                current_sum += a[k + 1];
                std::vector<long long> current = dp[i][k];
                std::vector<long long> current_whole = dp[0][k];
                current[0] = std::min<long long>(current_sum, current[0]);
                current[1] = std::max<long long>(current_sum, current[1]);
                current_whole[0] = std::min<long long>(current_sum, current_whole[0]);
                current_whole[1] = std::max<long long>(current_sum, current_whole[1]);
                if (current_whole[1] - current_whole[0] < current[1] - current[0])
                {
                    dp[i][j] = current_whole;
                }
                else
                {
                    dp[i][j] = current;
                }
                // std::cout << sum[k][j] << " ";
            }
            // std::cout << "best=" << best << std::endl;
        }
    }

    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[i].size(); j++)
        {
            std::cout << "{" << dp[i][j][0] << "," << dp[i][j][1] << "} ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------\n";
    return 3;
}
