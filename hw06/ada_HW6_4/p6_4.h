#include <bitset>
#include <vector>
using namespace std;

const int kN = 1024;
typedef std::bitset<kN> boolean_array;
typedef std::vector<boolean_array> boolean_matrix;

boolean_matrix boolean_matrix_multiplication(
    boolean_matrix A, boolean_matrix B);

boolean_matrix solve(int n, boolean_matrix g);
