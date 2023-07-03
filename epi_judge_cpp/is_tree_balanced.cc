#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int getDepth(BinaryTreeNode<int>* node) {
  if(node == nullptr) return 0;

  if(node->left == nullptr && node->right == nullptr) {
    return 1;
  } else {
    int left_d = getDepth(node->left.get());
    int right_d = getDepth(node->right.get());
    if(left_d == -1 || right_d == -1) return -1;
    else if(abs(left_d - right_d) > 1) return -1;
    else return std::max(left_d+1, right_d+1);
  }
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(tree.get() == nullptr) return true;
  if(getDepth(tree.get()) == -1) return false;
  else return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
