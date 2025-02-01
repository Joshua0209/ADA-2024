#include "p6_5.h"
#include <bits/stdc++.h>

bool solve(int n, std::vector<std::vector<int>> &c,
		   std::vector<int> &l, std::vector<int> &f)
{
	// I like money.
	std::vector<std::vector<double>> dist(n, std::vector<double>(n, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dist[i][j] = -log(c[i][j] * (1 - (double)f[i] / l[i]));
		}
	}
	// for (int i = 0; i < n; i++)
	// {
	// 	for (int j = 0; j < n; j++)
	// 	{
	// 		std::cout << dist[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	// for (int i = 0; i < n; i++)
	// {
	// 	for (int j = 0; j < n; j++)
	// 	{
	// 		std::cout << dist[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		if (dist[i][i] < 0)
		{
			return true;
		}
	}
	return false;
}
