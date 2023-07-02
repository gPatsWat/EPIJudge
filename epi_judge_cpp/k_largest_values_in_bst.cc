#include <cstddef>
#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void recursive(BstNode<int>* tree, vector<int>* ans, int k) {
  if(tree == nullptr) return;
  if(ans->size() == k) return;
  else {
    if(tree->right.get()) recursive(tree->right.get(), ans, k);
    if(ans->size() == k) return;
    ans->push_back(tree->data);
    if(ans->size() == k) return;
    if(tree->left.get()) recursive(tree->left.get(), ans, k);
  }
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  vector<int> ans;
  recursive(tree.get(), &ans, k);
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
