#include "p8_4.h"
#include <vector>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <tuple>

char buf[10];

int main() {
    int n, m, k;
    assert(1 == scanf("%d", &n));
    std::vector<std::tuple<std::string, std::vector<std::string>, int>> makefile(n);
    for (int i = 0; i < n; ++i) {
        std::string name;
        int k;
        assert(2 == scanf("%s%d", buf, &k));
        name = std::string(buf);
        std::vector<std::string> req(k);
        for(int j = 0; j < k; ++j) {
            assert(1 == scanf("%s", buf));
            req[j] = std::string(buf);
        }
        int comp_time;
        assert(1 == scanf("%d", &comp_time));
        makefile[i] = std::tuple<std::string, std::vector<std::string>, int>(name, req, comp_time);
   }
    long long ans = Minimum_Build_Time(makefile);
    printf("%lld\n", ans);    
    return 0;
}
