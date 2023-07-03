#include <limits>
#include <memory>

#include "binary_tree_node.h"
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool isBSTUtil(BinaryTreeNode<int>* tree, int mn, int mx) {
  if(!tree) return true;
  if(tree->data < mn || tree->data > mx) return false;

  return isBSTUtil(tree->left.get(), mn, tree->data) && isBSTUtil(tree->right.get(), tree->data, mx);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {

  return isBSTUtil(tree.get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
