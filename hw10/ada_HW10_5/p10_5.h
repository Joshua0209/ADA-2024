#include <utility>
#include <vector>
using namespace std;

pair<double, vector<double>>
lp_solver_max(const vector<vector<double>>& A,
              const vector<double>& b,
              const vector<double>& c);

double solve(int n, int m, vector<vector<int>> &a,
    vector<int>& b, vector<int>& p, vector<int>& c, vector<int>& d);
