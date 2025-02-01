#include "p11_4.h"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> MaxATSP(int n, int s, vector<vector<int>> W) {
    const ll INF = 1LL << 60;
    assert(2 <= n && n <= 22);
    assert(0 <= s && s < n);
    assert((int)W.size() == n);
    for(int i = 0; i < n; i++)
        assert((int)W[i].size() == n);

    vector<vector<ll>> dp(1 << n, vector<ll>(n, -INF));
    dp[1 << s][s] = 0;
    for(int mask = 0; mask < (1 << n); mask++) {
        for(int i = 0; i < n; i++) {
            if(~mask >> i & 1) continue;
            for(int j = 0; j < n; j++) {
                if(mask >> j & 1) continue;
                dp[mask | 1 << j][j] = max(dp[mask | 1 << j][j], dp[mask][i] + W[i][j]);
            }
        }
    }
	int best = -1;
	for(int i = 0; i < n; i++) {
		if(i == s) continue;
		if(best == -1 || dp[(1 << n) - 1][best] + W[best][s] < dp[(1 << n) - 1][i] + W[i][s])
			best = i;
	}
    vector<int> perm;
    int cur = best, mask = (1 << n) - 1;
    while(cur != s) {
        perm.push_back(cur);
        for(int i = 0; i < n; i++) {
            if(~mask >> i & 1) continue;
            if(i == cur) continue;
            if(dp[mask][cur] == dp[mask ^ (1 << cur)][i] + W[i][cur]) {
                mask ^= 1 << cur;
                cur = i;
                break;
            }
        }
    }
    perm.push_back(s);
    reverse(perm.begin(), perm.end());
    return perm;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> S(n);
    for(int i = 0; i < n; i++)
        cin >> S[i];
    string res = SSP(n, S);
    cout << res << '\n';
}
