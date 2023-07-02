#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> ans;
  int i = 0,j = 0;

  while(i < A.size() && j < B.size()) {
    if(A[i] < B[j]) {
      while(i < A.size() && A[i] < B[j]) i++;
    }
    else if(A[i] > B[j]) {
      while(j < B.size() && A[i] > B[j]) j++;
    }
    else if(A[i] == B[j]) {
      ans.push_back(A[i]);
      int temp = A[i];
      while(i < A.size() && A[i] == temp) i++;
      while(j < B.size() && B[j] == temp) j++;
    }
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
