#include "p5_5.h"
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>

int main() {
    int n, m;
    assert(2 == scanf("%d%d", &n, &m));
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i)
        assert(2 == scanf("%d%d", &edges[i].first, &edges[i].second));
    std::vector<int> ans = Eulerian_circuit(n, edges);
    for(int i = 0; i < ((int)(ans.size())); i++) {
        printf("%d", ans[i]);
        if(i == ((int)(ans.size()) - 1))
            printf("\n");
        else printf(" ");
    }
    return 0;
}
