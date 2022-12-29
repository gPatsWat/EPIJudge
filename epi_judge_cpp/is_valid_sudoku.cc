#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  vector<bool> hset(10,0), vset(10,0);
  for(int i = 0;i<9;i++) {
    for(int j=0;j<9;j++) {
      if(partial_assignment[i][j] != 0 && hset[partial_assignment[i][j]] == 1) {
        return false;
      }
      else if(partial_assignment[i][j] != 0) hset[partial_assignment[i][j]] = 1;

      if(partial_assignment[j][i] != 0 && vset[partial_assignment[j][i]] == 1) {
        return false;
      }
      else if(partial_assignment[j][i] != 0) vset[partial_assignment[j][i]] = 1;
    }
    std::fill(hset.begin(), hset.end(), 0);
    std::fill(vset.begin(), vset.end(), 0);
  }

  std::fill(hset.begin(), hset.end(), 0);

  for(int i=0;i<3;i++) {
    for(int j=0;j<3;j++) {
      for(int k=0;k<9;k++) {
        if(partial_assignment[3*i + k/3][3*j + k%3] != 0 && hset[partial_assignment[3*i + k/3][3*j + k%3]] == 1) {
          std::cout << "sq false" << std::endl;
          return false;
        }
        else if(partial_assignment[3*i + k/3][3*j + k%3] != 0) hset[partial_assignment[3*i + k/3][3*j + k%3]] = 1;
      }
      std::fill(hset.begin(), hset.end(), 0);
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
