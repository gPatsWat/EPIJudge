#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool isSymmetric(BinaryTreeNode<int>* left, BinaryTreeNode<int>* right) {
  if(left && right) {
    if(left->data == right->data) {
      if(isSymmetric(left->right.get(), right->left.get()) && isSymmetric(left->left.get(), right->right.get()))
      return true;
    }
  }
  else if(!left && !right) return true;
  return false;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(tree.get() == nullptr) return true;
  if(tree->left == nullptr && tree->right == nullptr) return true;
  else if(tree->left != nullptr && tree->right != nullptr) return isSymmetric(tree->left.get(), tree->right.get()
  );
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
