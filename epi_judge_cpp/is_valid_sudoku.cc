#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  int hset[9], vset[9];
  memset(hset, 0, 9);
  memset(vset, 0, 9);

  for(int i = 0;i < 9;i++) {
    for(int j = 0;j < 9;j++) {
      if(partial_assignment[i][j] != 0 && hset[partial_assignment[i][j]-1] == 1) return false;
      else if(partial_assignment[i][j] != 0) hset[partial_assignment[i][j]-1] = 1;

      if(partial_assignment[i][j] != 0 && vset[partial_assignment[j][i] - 1] == 1) return false;
      else if(partial_assignment[i][j] != 0) vset[partial_assignment[j][i] - 1] = 1;
    }
    memset(hset, 0, 9);
    memset(vset, 0, 9);
  }

  for(int i = 0;i < 3;i++) {
    for(int j = 0;j < 3;j++) {
      for(int k = 0;k < 9;k++) {
        if(partial_assignment[i][j] != 0 && hset[partial_assignment[(i+k)/3][(j+k)%3] - 1] == 1) return false;
        else if(partial_assignment[i][j] != 0) hset[partial_assignment[(i+k)/3][(j+k)%3] - 1] = 1;
      }
      memset(hset, 0, 9);
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
