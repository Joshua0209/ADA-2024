#include "p2_5.h"
#include <cassert>
#include <cstdio>
#include <vector>

int main()
{
  int N, M;
  assert(2 == scanf("%d%d", &N, &M));

  std::vector<int> l1(N + 1), r1(N + 1), s1(N + 1);
  std::vector<int> l2(M + 1), r2(M + 1), s2(M + 1);
  for (int i = 1; i <= N; ++i)
    scanf("%d", &l1[i]);
  for (int i = 1; i <= N; ++i)
    scanf("%d", &r1[i]);
  for (int i = 1; i <= N; ++i)
    scanf("%d", &s1[i]);
  for (int i = 1; i <= M; ++i)
    scanf("%d", &l2[i]);
  for (int i = 1; i <= M; ++i)
    scanf("%d", &r2[i]);
  for (int i = 1; i <= M; ++i)
    scanf("%d", &s2[i]);

  printf("%lld\n", solve(N, M, l1, r1, s1, l2, r2, s2));

  return 0;
}
