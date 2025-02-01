#include "p9_4.h"
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>

int main() {
    int n, m;
    assert(2 == scanf("%d%d", &n, &m));
    std::vector<std::pair<int, int>> edges(m);
    std::vector<int> capv(n - 2), cape(m);
    for (int i = 0; i < n - 2; ++i)
        assert(1 == scanf("%d", &capv[i]));
    for (int i = 0; i < m; ++i)
        assert(3 == scanf("%d%d%d", &edges[i].first, &edges[i].second, &cape[i]));
    int ans = Maximum_Flow(n, edges, capv, cape);
    printf("%d\n", ans);    
    return 0;
}
