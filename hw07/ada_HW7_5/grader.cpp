#include "p7_5.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	int n, m, k, s, t;
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
	vector<int> u(m), v(m), w(m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &u[i], &v[i], &w[i]);
	}
	vector<int> res = solve(n, m, k, s, t, u, v, w);
	printf("%d\n", (int)res.size());
	for(int i = 0; i < (int)res.size(); i++) {
		printf("%d", res[i]);
		if(i + 1 < (int)res.size()) {
			printf(" ");
		}
		else {
			printf("\n");
		}
	}
	return 0;
}
