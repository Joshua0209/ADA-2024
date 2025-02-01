#include "p1_5.h"

#include <cstdio>
#include <vector>
#include <string>

namespace {

}

int main() {
	int n, K;
	scanf("%d%d", &n, &K);
	std::vector<std::string> s(K, std::string(K, '.'));
	for(int i = 0; i < K; i++) scanf(("%" + std::to_string(K) + "s").c_str(), &s[i][0]);
	int res = count_polyominoes(n, K, s);
	printf("%d\n", res);
	return 0;
}
