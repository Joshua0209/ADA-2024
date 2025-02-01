#include "p3_5.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <algorithm>

int minimum_possible_unbalancedness(std::vector<int> &a)
{
    std::vector<std::vector<std::vector<long long>>> dp(a.size() + 1, std::vector<std::vector<long long>>(a.size() + 1, std::vector<long long>(2, 0)));
    std::vector<std::vector<long long>> sum(a.size() + 1, std::vector<long long>(a.size() + 1, 0));
    for (int i = 0; i < sum.size(); i++)
    {
        for (int j = i + 1; j < sum[i].size(); j++)
        {
            sum[i][j] = sum[i][j - 1] + a[j - 1];
        }
    }
    for (int i = 1; i < a.size() + 1; i++)
    {
        dp[1][i] = {sum[0][i], sum[0][i]};
        dp[i][1] = {a[0], a[0]};
    }
    for (int i = 2; i < dp.size(); i++)
    {
        for (int j = 2; j < dp[i].size(); j++)
        {
            std::vector<long long> best = {LLONG_MAX, 0};
            for (int k = 0; k < j; k++)
            {
                // std::cout << "i=" << i << " j=" << j << "\n";
                if (dp[i - 1][k][0] < sum[k][j])
                {
                    if (sum[k][j] < best[0])
                    {
                        best[0] = sum[k][j];
                        best[1] = dp[i - 1][k][1];
                    }
                }
                else if (dp[i - 1][k][0] > sum[k][j])
                {
                    if (dp[i - 1][k][0] < best[0])
                    {
                        best[0] = dp[i - 1][k][0];
                        best[1] = std::min<long long>(sum[k][j], dp[i - 1][k][1]);
                    }
                }
                else
                {
                    if (sum[k][j] >= best[1])
                    {
                        best[0] = dp[i - 1][k][0];
                        best[1] = dp[i - 1][k][1];
                    }
                }
                // std::cout << sum[k][j] << " ";
            }
            // std::cout << "best=" << best << std::endl;
            dp[i][j] = best;
        }
    }
    // for (int i = 0; i < sum.size(); i++)
    // {
    //     for (int j = 0; j < sum[i].size(); j++)
    //     {
    //         std::cout << sum[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "---------------\n";
    // for (int i = 0; i < dp.size(); i++)
    // {
    //     for (int j = 0; j < dp[i].size(); j++)
    //     {
    //         std::cout << "{" << dp[i][j][0] << "," << dp[i][j][1] << "} ";
    //     }
    //     std::cout << std::endl;
    // }
    long long best_unbalancedness = LLONG_MAX;
    for (int i = 2; i < dp.size(); i++)
    {
        long long tmp = dp[i][dp[i].size() - 1][0] - dp[i][dp[i].size() - 1][1];
        if (best_unbalancedness > tmp)
        {
            best_unbalancedness = tmp;
        }
    }
    return best_unbalancedness;
}
