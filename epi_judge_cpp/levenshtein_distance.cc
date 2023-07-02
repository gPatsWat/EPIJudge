#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int comp_dist(const string& A, const string& B, int a, int b, vector<vector<int>>& dp) {
//   std::cout << a << std::endl;
  if(a < 0) {
    return b+1;
  }
  else if(b < 0) return a+1;

  if(dp[a][b] == -1) {
    if(A[a] == B[b]) {
        dp[a][b] = comp_dist(A, B, a-1, b-1, dp);
    } else {
        int x = 1 + comp_dist(A, B, a, b-1, dp);
        int y = 1 + comp_dist(A, B, a-1, b, dp);
        int z = 1 + comp_dist(A, B, a-1, b-1, dp);
        dp[a][b] = std::min(std::min(x,y), z);
    }
  }
  return dp[a][b];
}
int LevenshteinDistance(const string& A, const string& B) {
  vector<vector<int>> dp(A.size(), vector<int>(B.size(), -1));
  return comp_dist(A, B, A.size()-1, B.size()-1, dp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
