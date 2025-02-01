#include "p1_6.h"
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

int main() {
  int N;
	assert(1 == scanf("%d", &N));

  char buffer[10];
  std::vector<std::vector<std::string>> board(7);
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 7; ++j) {
      assert(1 == scanf("%s", buffer));
      board[i].emplace_back(buffer);
    }
  }

  std::vector<std::vector<std::string>> polyominos(N);
  for (int i = 0; i < N; ++i) {
    int L, W;
    assert(2 == scanf("%d%d", &L, &W));
    for (int l = 0; l < L; ++l) {
      assert(1 == scanf("%s", buffer));
      polyominos[i].emplace_back(buffer);
      assert((int) polyominos[i][l].size() == W);
    }
  }

  std::vector<std::string> res = find_unsolvable_dates(board, polyominos);
  std::sort(res.begin(), res.end());
  // BEGIN SECRET
  printf("OK\n");
  // END SECRET
  for (std::string &s : res)
    puts(s.c_str());

	return 0;
}
