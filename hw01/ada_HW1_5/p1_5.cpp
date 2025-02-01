#include "p1_5.h"
#include <vector>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, bool> polyominoes;
std::unordered_map<std::string, bool> memo;
std::vector<std::string> s;
int K;
int count;

bool check_memo(std::vector<std::string> tmp)
{
	std::string encoded;
	for (const auto &row : tmp)
	{
		encoded += row;
	}

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (s[i][j] == 'x')
			{
				encoded[i * K + j] = 'x';
			}
		}
	}

	if (memo.find(encoded) != memo.end())
	{
		return true;
	}

	std::vector<std::string> grid_keys(8);
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			grid_keys[0] += s[i][j] == 'x' ? 'x' : tmp[i][j];
			grid_keys[1] += s[K - i - 1][j] == 'x' ? 'x' : tmp[K - i - 1][j];
			grid_keys[2] += s[i][K - j - 1] == 'x' ? 'x' : tmp[i][K - j - 1];
			grid_keys[3] += s[K - i - 1][K - j - 1] == 'x' ? 'x' : tmp[K - i - 1][K - j - 1];
			grid_keys[4] += s[j][K - i - 1] == 'x' ? 'x' : tmp[j][K - i - 1];
			grid_keys[5] += s[K - j - 1][i] == 'x' ? 'x' : tmp[K - j - 1][i];
			grid_keys[6] += s[j][i] == 'x' ? 'x' : tmp[j][i];
			grid_keys[7] += s[K - j - 1][K - i - 1] == 'x' ? 'x' : tmp[K - j - 1][K - i - 1];
		}
	}

	for (int i = 0; i < grid_keys.size(); i++)
	{
		memo[grid_keys[i]] = true;
	}
	return false;
}

void check_poly(std::vector<std::string> tmp)
{
	std::string encoded;
	for (const auto &row : tmp)
	{
		encoded += row;
	}

	if (polyominoes.find(encoded) != polyominoes.end())
	{
		return;
	}

	std::vector<std::string> grid_keys(8);
	grid_keys[0] = encoded;
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			grid_keys[1] += tmp[K - i - 1][j];
			grid_keys[2] += tmp[i][K - j - 1];
			grid_keys[3] += tmp[K - i - 1][K - j - 1];
			grid_keys[4] += tmp[j][K - i - 1];
			grid_keys[5] += tmp[K - j - 1][i];
			grid_keys[6] += tmp[j][i];
			grid_keys[7] += tmp[K - j - 1][K - i - 1];
		}
	}

	for (int i = 0; i < grid_keys.size(); i++)
	{
		polyominoes[grid_keys[i]] = true;
	}
	count++;
	return;
}

void analyze(std::vector<std::string> org)
{
	bool flag = false;
	for (int i = 0; i < org.size(); i++)
	{
		if (org[0][i] != '0')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
		return;
	else
		flag = false;

	for (int i = 0; i < org.size(); i++)
	{
		if (org[org.size() - 1][i] != '0')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
		return;
	else
		flag = false;

	for (int i = 0; i < org.size(); i++)
	{
		if (org[i][0] != '0')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
		return;
	else
		flag = false;

	for (int i = 0; i < org.size(); i++)
	{
		if (org[i][org.size() - 1] != '0')
		{
			flag = true;
			break;
		}
	}
	if (!flag)
		return;
	else
		flag = false;

	check_poly(org);
	return;
}

void recur_count(int n, std::vector<std::string> tmp)
{
	if (n == 0)
	{
		analyze(tmp);
		return;
	}
	if (check_memo(tmp))
	{
		return; // Skip if already processed
	}

	for (int _i = 0; _i < K; _i++)
	{
		for (int _j = 0; _j < K; _j++)
		{
			if (tmp[_i][_j] == '0')
			{
				continue;
			}
			// left
			if (_j + 1 < K && s[_i][_j + 1] == '.' && tmp[_i][_j + 1] == '0')
			{
				tmp[_i][_j + 1] = '1';
				recur_count(n - 1, tmp);
				tmp[_i][_j + 1] = '0';
			}
			// right
			if (_j > 0 && s[_i][_j - 1] == '.' && tmp[_i][_j - 1] == '0')
			{
				tmp[_i][_j - 1] = '1';
				recur_count(n - 1, tmp);
				tmp[_i][_j - 1] = '0';
			}
			// up
			if (_i > 0 && s[_i - 1][_j] == '.' && tmp[_i - 1][_j] == '0')
			{
				tmp[_i - 1][_j] = '1';
				recur_count(n - 1, tmp);
				tmp[_i - 1][_j] = '0';
			}
			// down
			if (_i + 1 < K && s[_i + 1][_j] == '.' && tmp[_i + 1][_j] == '0')
			{
				tmp[_i + 1][_j] = '1';
				recur_count(n - 1, tmp);
				tmp[_i + 1][_j] = '0';
			}
		}
	}
}

int count_polyominoes(int n, int K, std::vector<std::string> s)
{
	std::vector<std::string> tmp(K, std::string(K, '0'));
	::s = s;
	::K = K;

	int dot_count = 0;
	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (s[i][j] == '.')
			{
				dot_count++;
			}
		}
	}
	if (dot_count < n)
	{
		return 0;
	}

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < K; j++)
		{
			if (s[i][j] == '.')
			{
				tmp[i][j] = '1';
				recur_count(n - 1, tmp);
				tmp[i][j] = '0';
			}
		}
	}
	return count;
}
