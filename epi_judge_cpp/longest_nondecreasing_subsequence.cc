#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
  vector<int> dp(A.size(), 0);
  if(A.empty()) return 0;
  dp[0] = 1;

  for(int i = 1;i<dp.size();i++) {
    int maxdp = std::numeric_limits<int>::min();
    for(int j = 0;j<i;j++) {
      if(A[j] <= A[i])
        maxdp = std::max(maxdp, dp[j]);
    }
    if(maxdp == std::numeric_limits<int>::min())
      dp[i] = 1;
    else dp[i] = maxdp+1;
  }

  int maxsol = dp[0];
  for(int i = 0;i < dp.size();i++) {
    maxsol = std::max(maxsol, dp[i]);
  }
  return maxsol;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
                         "longest_nondecreasing_subsequence.tsv",
                         &LongestNondecreasingSubsequenceLength,
                         DefaultComparator{}, param_names);
}
