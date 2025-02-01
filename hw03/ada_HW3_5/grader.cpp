#include "p3_5.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>

int main()
{
    int n;
    assert(1 == scanf("%d", &n));
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)
        assert(1 == scanf("%d", &a[i]));
    int ans = minimum_possible_unbalancedness(a);
    printf("%d\n", ans);
    return 0;
}
