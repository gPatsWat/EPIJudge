#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  int k = m+n-1, i = m-1, j = n-1;

  while(i >= 0 && j >= 0) {
    if(A[i] >= B[j]) {
      A[k] = A[i];
      i--;
      k--;
    } else if(A[i] < B[j]) {
      A[k] = B[j];
      j--;
      k--;
    }
  }

  while(i >= 0) {
    A[k] = A[i];
    i--;
    k--;
  }
  while(j >= 0) {
    A[k] = B[j];
    j--;
    k--;
  }
  return;
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
