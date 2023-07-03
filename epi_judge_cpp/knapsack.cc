#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  vector<std::vector<int>> dp(items.size(), vector<int>(capacity+1, 0));
  if(items.empty()) return 0;
  for(int j = 1;j < dp[0].size();j++) {
    if(items[0].weight < j) dp[0][j] = items[0].value;
  }

  for(int i = 1;i < items.size();i++) {
    for(int j = 1;j < dp[0].size();j++) {
      if(j >= items[i].weight) {
        dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-items[i].weight]+items[i].value);
      }
      else dp[i][j] = dp[i-1][j];
    }
  }

  return dp[items.size()-1][capacity];
}
namespace test_framework {
template <>
struct SerializationTrait<Item> : UserSerTrait<Item, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
