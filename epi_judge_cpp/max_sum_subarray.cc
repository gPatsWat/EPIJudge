#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindMaximumSubarray(const vector<int>& A) {
  if(A.size() == 0) return 0;
  int maxelem = std::numeric_limits<int>::min();
  vector<int> dp(A.size(), 0);
  dp[0] = A[0] > 0 ? A[0] : 0;
  maxelem = dp[0];
  for(int i = 0 ;i < A.size();i++) {
    if(dp[i-1] + A[i] > A[i])
      dp[i] = dp[i-1] + A[i];
    else dp[i] = A[i];

    if(maxelem < dp[i]) maxelem = dp[i];
  }
  return maxelem;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "max_sum_subarray.cc", "max_sum_subarray.tsv",
                         &FindMaximumSubarray, DefaultComparator{},
                         param_names);
}
