#include "p3_5.h"
#include <vector>
#include <cmath>
#include <climits>
#include <iostream>
#include <bitset>
#include <algorithm>

long long length(std::vector<int>& a, int start, int end) {
    long long result = 0;
    for (int i = start; i < end; i++) {
        result += a[i];
    }
    return result;
}

long long unbalanceness(std::vector<long long>& l) {
    if (l.empty()) return 0;
    long long max_val = *std::max_element(l.begin(), l.end());
    long long min_val = *std::min_element(l.begin(), l.end());
    return max_val - min_val;
}

int minimum_possible_unbalancedness(std::vector<int>& a) {
    int min_unbalanceness = INT_MAX;
    int n = a.size();
    
    for (long long i = 1; i < (1LL << (n - 1)); i++) { // Iterate from 1 to 2^(n-1) - 1
        std::vector<long long> l;
        int prev = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1LL << j)) { // Check if the jth bit is set
                l.push_back(length(a, prev, j + 1));
                prev = j + 1;
            }
        }
        l.push_back(length(a, prev, n)); // Final partition

        long long current_unbalanceness = unbalanceness(l);
        if (current_unbalanceness < min_unbalanceness) {
            min_unbalanceness = current_unbalanceness;
        }
    }
    
    return min_unbalanceness;
}
