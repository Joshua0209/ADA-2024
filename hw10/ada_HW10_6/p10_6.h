#include <utility>
#include <vector>
using namespace std;

pair<long double, vector<long double>>
lp_solver_max(const vector<vector<long double>>& A,
              const vector<long double>& b,
              const vector<long double>& c);
double max_profit_to_ratio(int n, int m, int l, int C,
                vector<vector<int>> &a, vector<int> &c,
                vector<int> &d, vector<vector<int>> &f,
                vector<int> &g, vector<int> &h,
                vector<int> &p, vector<int> &q);
