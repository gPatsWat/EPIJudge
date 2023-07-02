#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
  BstNode<int>* firstgk = nullptr, *iter = tree.get();

  while(iter != nullptr) {
    if(iter->data <= k) {
      iter = iter->right.get();
    }
    else if(iter->data > k) {
      if(firstgk == nullptr) firstgk = iter;
      else if(firstgk->data - k > iter->data - k) firstgk = iter;

      iter = iter->left.get();
    }
  }
  return firstgk;
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
