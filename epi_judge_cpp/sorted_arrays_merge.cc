#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  std::priority_queue<std::pair<int,int>, vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  vector<int> index_arr(sorted_arrays.size(), 0);

  if(sorted_arrays.empty()) return {};

  int num_elements = 0;
  for(int i = 0;i < sorted_arrays.size();i++) {
    num_elements += sorted_arrays[i].size();
  }

  vector<int> ans;

  for(int i = 0;i < sorted_arrays.size();i++) {
    if(sorted_arrays[i].empty()) continue;
    else {
      pq.push({sorted_arrays[i][0], i});
    }
  }

  for(int num = 0;num < num_elements;num++) {
    if(!pq.empty()) {
      auto elem = pq.top();
      pq.pop();
      // std::cout << "popping: " << elem.first << " array: " << elem.second << " index: "<< index_arr[elem.second] << std::endl;
      ans.push_back(elem.first);
      index_arr[elem.second]++;
      if(index_arr[elem.second] < sorted_arrays[elem.second].size()) {
        pq.push({sorted_arrays[elem.second][index_arr[elem.second]], elem.second});
        // std::cout << "pushing: " << sorted_arrays[elem.second][index_arr[elem.second]] << "array: " << elem.second <<std::endl;
      }
    }
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
