#include "p6_6.h"
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>

int main() {
    int n, m, k;
    assert(3 == scanf("%d%d%d", &n, &m, &k));
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i)
        assert(2 == scanf("%d%d", &edges[i].first, &edges[i].second));
    std::vector<int> weights(m);
    for(int i = 0; i < m; ++i)
        assert(1 == scanf("%d", &weights[i]));
    std::vector<int> stars(k);
    for(int i = 0; i < k; ++i)
        assert(1 == scanf("%d", &stars[i]));
    std::vector<std::vector<long long>> ans = Shortest_2Stars_Time(n, edges, weights, stars);
    for(int i = 0; i < ((int)(ans.size())); ++i) {
        for(int j = 0; j < ((int)(ans[i].size())); ++j) {
            printf("%lld", ans[i][j]);
            if(j != ((int)(ans[i].size()) - 1))
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
