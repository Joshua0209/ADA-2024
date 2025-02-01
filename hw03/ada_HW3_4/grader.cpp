#include "p3_4.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace {

}

int main() {
	int M, N;
	scanf("%d%d", &M, &N);
	std::vector<std::vector<int>> c(M, std::vector<int>(N));
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%d", &c[i][j]);
		}
	}
	int res = largest_square(M, N, c);
	printf("%d\n", res);
	return 0;
}
