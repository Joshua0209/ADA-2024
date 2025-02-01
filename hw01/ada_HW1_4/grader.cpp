#include "p1_4.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <string>

int main() {
    int n, m;
    assert(2 == scanf("%d%d", &n, &m));
    std::vector<std::string> A(n), B(n);
    for (int i = 0; i < n; ++i) {
        char str[m + 1];
        assert(1 == scanf("%s", str));
        A[i] = str;
    }
    for (int i = 0; i < n; ++i) {
        char str[m + 1];
        assert(1 == scanf("%s", str));
        B[i] = str;
    }
    int ans;
    if(compare_polyominoes(A, B)) printf("YES\n");
    else printf("NO\n");
    return 0;
}
