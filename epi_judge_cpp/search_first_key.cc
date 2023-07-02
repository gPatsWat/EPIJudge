#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  if(A.empty()) return -1;
  int l = 0, r = A.size() - 1, mid = l + (r-l)/2;
  while(l <= r) {
    mid = l + (r-l)/2;
    if(A[mid] == k) {
      while(mid >= 0 && A[mid] == k) mid--;
      return mid+1;
    }
    else if(A[mid] < k) {
      l = mid+1;
    }
    else r = mid-1;
  }
  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
