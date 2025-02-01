#include "p8_6.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> u(m), v(m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &u[i], &v[i]);
	}
	long long res = solve(n, m, u, v);
	printf("%lld\n", res);
	return 0;
}
