#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  std::priority_queue<int,vector<int>,std::greater<int>> pq;
  if(A_ptr->empty()) return 0;

  for(int i = 0;i < A_ptr->size();i++) {
    if(pq.size() == k) {
      if((*A_ptr)[i] > pq.top()) {
        pq.pop();
        pq.push((*A_ptr)[i]);
      }
    }
    else pq.push((*A_ptr)[i]);
  }
  return pq.top();
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
