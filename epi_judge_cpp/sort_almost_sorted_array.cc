#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  if(sequence_end - sequence_begin <= k) {
    std::priority_queue<int, vector<int>, std::greater<int>> pq(sequence_begin, sequence_end);
    vector<int> ans;
    while(!pq.empty()) {
      ans.push_back(pq.top());
      pq.pop();
    }

    return ans;
  }
  else {
    std::priority_queue<int, vector<int>, std::greater<int>> pq(sequence_begin, sequence_begin + k);
    auto iter = sequence_begin + k;
    vector<int> ans;
    while(!pq.empty()) {
      ans.push_back(pq.top());
      pq.pop();
      if(iter != sequence_end) {
        pq.push(*iter);
        iter++;
      }
    }

    return ans;
  }


  return {};
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
