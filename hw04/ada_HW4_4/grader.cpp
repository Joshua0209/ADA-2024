#include "p4_4.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

int main() {
    int n, a, b;
    long long t;
    assert(4 == scanf("%d%d%d%lld", &n, &a, &b, &t));
    std::vector<int> dishes(n);
    for (int i = 0; i < n; ++i)
        assert(1 == scanf("%d", &dishes[i]));
    int ans = maximum_dishes(dishes, a, b, t);
    printf("%d\n", ans);
    return 0;
}
