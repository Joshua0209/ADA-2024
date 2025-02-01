#include "p6_5.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	for(int tst = 1; tst <= T; tst++) {
		int n;
		scanf("%d", &n);
		
		vector<vector<int>> c(n, vector<int>(n));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &c[i][j]);
			}
		}

		vector<int> l(n), f(n);
		for(int i = 0; i < n; i++)
			scanf("%d", &l[i]);
		for(int i = 0; i < n; i++)
			scanf("%d", &f[i]);

		bool res = solve(n, c, l, f);
		if(res)
			printf("true\n");
		else
			printf("false\n");
	}
	return 0;
}
