#include "p9_6.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	int m, n, X, Y;
	scanf("%d%d%d%d", &m, &n, &X, &Y);
	vector<vector<int>> C(m, vector<int>(n));
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			scanf("%d", &C[i][j]);
	long long res = max_profit(m, n, X, Y, C);
	printf("%lld\n", res);
	return 0;
}
