#include "p5_4.h"

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
	vector<int> state = assign_states(n, m, u, v);
	for(int i = 0; i < (int)state.size(); i++)
	{
		printf("%d", state[i]);
		if(i + 1 < (int)state.size()) printf(" ");
		else printf("\n");
	}
	return 0;
}
