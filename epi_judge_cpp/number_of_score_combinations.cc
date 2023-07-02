#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  vector<vector<int>> dp(individual_play_scores.size(), vector<int>(final_score+1, 0));
  for(int i = 1;i < final_score+1;i++) {
    if(i%individual_play_scores[0] == 0)
      dp[0][i] = 1;
  }

  for(int i = 0;i < individual_play_scores.size();i++) {
    dp[i][0] = 1;
  }

  for(int i = 1;i < individual_play_scores.size();i++) {
    for(int j = 1;j < final_score+1; j++) {
        dp[i][j] = 0;
      for(int k = 0;j - k*individual_play_scores[i] >= 0;k++) {
        // std::cout << i << " " << j << " " << j - k*individual_play_scores[i] << std::endl;
        dp[i][j] += dp[i-1][j-k*individual_play_scores[i]];
      }
      // std::cout << dp[i][j] << std::endl;
    }
  }

  return dp[individual_play_scores.size()-1][final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
