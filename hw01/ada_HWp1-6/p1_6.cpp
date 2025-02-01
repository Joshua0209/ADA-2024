#include "p1_6.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include <map>

vector<vector<string>> board;
vector<vector<string>> polyominos;
std::map<std::string, int> daysInMonth = {
    {"Jan", 31}, // January
    {"Feb", 29}, // February
    {"Mar", 31}, // March
    {"Apr", 30}, // April
    {"May", 31}, // May
    {"Jun", 30}, // June
    {"Jul", 31}, // July
    {"Aug", 31}, // August
    {"Sep", 30}, // September
    {"Oct", 31}, // October
    {"Nov", 30}, // November
    {"Dec", 31}, // December
    {"X", 0}};
vector<string> unsol;

void solve_date(vector<int> date)
{
  cout << board[date[0]][date[1]] << board[date[2]][date[3]] << " ";
}

vector<int> next_date(vector<int> input_date)
{
  int row_month = input_date[0], col_month = input_date[1], row_date = input_date[2], col_date = input_date[3];
  if (std::stoi(board[row_date][col_date]) < daysInMonth[board[row_month][col_month]])
  {
    if (col_date + 1 < board[row_date].size() && board[row_date][col_date + 1] != "X")
      col_date++;
    else
    {
      if (row_date + 1 < board.size())
      {
        row_date++;
        col_date = 0;
        while (board[row_date][col_date] == "X")
          col_date++;
      }
    }
  }
  else if (board[row_month][col_month] != "Dec")
  {
    if (col_month + 1 < board[row_month].size() && board[row_month][col_month + 1] != "X")
      col_month++;
    else
    {
      row_month = 1;
      col_month = 0;
      while (board[row_month][col_month] == "X")
        col_month++;
    }
    row_date = 2;
    col_date = 0;
    while (board[row_date][col_date] == "X")
    {
      col_date++;
    }
  }
  else
  {
    return {-1, -1, -1, -1}; // final
  }
  return {row_month, col_month, row_date, col_date};
}

vector<string> find_unsolvable_dates(vector<vector<string>> board,
                                     vector<vector<string>> polyominos)
{
  ::board = board;
  ::polyominos = polyominos;
  vector<int> date = {0, 0, 2, 0}; // row_month = 0, col_month = 0, row_date = 3, col_date = 0
  while (date[0] != -1)
  {
    solve_date(date);
    date = next_date(date);
  }
  return unsol;
}
