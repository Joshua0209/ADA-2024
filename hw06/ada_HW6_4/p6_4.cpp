#include "p6_4.h"
#include <bits/stdc++.h>
using namespace std;

boolean_matrix solve(int n, boolean_matrix g)
{
  boolean_matrix r(g);
  for (int i = 0; i < n; i++)
  {
    r = boolean_matrix_multiplication(g, g);
    bool change = false;
    for (int i = 0; i < n; i++)
    {
      if (r[i] != g[i])
      {
        change = true;
        break;
      }
    }
    if (!change)
    {
      break;
    }
    g = r;
  }
  return r;
}
