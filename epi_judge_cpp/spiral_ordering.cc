#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  int direction = 0, i = 0, j = 0;

  if(square_matrix.size() == 0) return {};

  int left = 0, right = square_matrix[0].size()-1;
  int top = 0, bottom = square_matrix.size()-1;
  vector<int> sp;

  // (top <= i <= bottom) && (left <= j <= right) does NOT mean the same as (top <= i) && (i <= bottom)
  // while((top <= i <= bottom) && (left <= j <= right)) {
  while((top <= i) && (i <= bottom) && (left <= j) &&  (j <= right)) {
    sp.push_back(square_matrix[i][j]);
    switch (direction) {
      case 0:
      if(j == right) {
        direction = 1;
        top++;
        i++;
      }
      else j++;
      break;
      case 1:
      if(i == bottom) {
        direction = 2;
        right--;
        j--;
      }
      else i++;
      break;
      case 2:
      if(j == left) {
        direction = 3;
        bottom--;
        i--;
      }
      else j--;
      break;
      case 3:
      if(i == top) {
        direction = 0;
        left++;
        j++;
      }
      else i--;
      break;
    }
  }

  return sp;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
