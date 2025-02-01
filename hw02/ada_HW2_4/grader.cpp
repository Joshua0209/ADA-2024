#include "p2_4.h"
#include <cassert>
#include <cstdio>
#include <string>


namespace {
    int n;
    const int MAX_N = 5140;
    int direction[MAX_N + 1][MAX_N + 1];
    int query_count = 0;
    const int MAX_QUERY = 78000;
    void quit(const char *type, const char *msg) {
        printf("%s: %s\n", type, msg);
        fclose(stdout);
        exit(0);
    }
}

int get_result(int x, int y) {
    if (x < 1 || n < x || y < 1 || n < y)
        quit("Wrong Answer", "invalid query");
    if (x == y)
        quit("Wrong Answer", "invalid query");
    query_count++;
    if (query_count > MAX_QUERY)
        quit("Wrong Answer", "too many queries");
    return direction[x][y];
}

int main() {
    assert(1 == scanf("%d", &n));
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++) {
            assert(1 == scanf("%d", &direction[i][j]));
            direction[j][i] = !direction[i][j];
        }

    fclose(stdin);

    std::vector<int> res = find_permutation(n);
    if ((int) res.size() != n)
        quit("Wrong Answer", "not a permutation");
    std::vector<bool> used(n + 1);
    for (int i = 0; i < n; i++) {
        if (res[i] < 1 || n < res[i])
            quit("Wrong Answer", "not a permutation");
    }
    for (int i = 0; i + 1 < n; i++) {
        if (direction[res[i]][res[i + 1]] == 0)
            quit("Wrong Answer", "invalid permutation");
    }

    quit("Accepted", ("number of queries: " + std::to_string(query_count)).c_str());
}
