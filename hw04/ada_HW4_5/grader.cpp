#include "p4_5.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	int n, L, R;
	long long k;
	scanf("%d%lld%d%d", &n, &k, &L, &R);
	vector<int> c(n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &c[i]);
	}
	vector<long long> ans = count_sets(n, k, L, R, c);
	for(int i = 0; i < (int)ans.size(); i++)
	{
		printf("%lld", ans[i]);
		if(i + 1 < (int)ans.size()) printf(" ");
		else printf("\n");
	}
	return 0;
}
