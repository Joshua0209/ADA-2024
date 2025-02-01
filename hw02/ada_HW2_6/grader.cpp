#include "p2_6.h"

#include <cstdio>
#include <vector>
#include <string>

namespace {

}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	std::string v(k, '0');
	std::vector<std::string> s(n, std::string(k, '0'));
	scanf(("%" + std::to_string(k) + "s").c_str(), &v[0]);
	for(int i = 0; i < n; i++) scanf(("%" + std::to_string(k) + "s").c_str(), &s[i][0]);
	int res = solve(n, k, v, s);
	printf("%d\n", res);
	return 0;
}
