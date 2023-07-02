#include "test_framework/generic_test.h"

int dp_solver(int n, int m, std::vector<std::vector<int>>& dp) {
  if(n == 0) return 1;
  else if(m == 0) return 1;

  if(dp[n][m] == 0) {
    dp[n][m] = dp_solver(n-1, m, dp) + dp_solver(n, m-1, dp);
  }

  return dp[n][m];
}

int NumberOfWays(int n, int m) {
  if(!(n > 0 && m > 0)) return 0;
  std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
  return dp_solver(n-1, m-1, dp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
