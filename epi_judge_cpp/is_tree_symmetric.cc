#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <cstddef>

bool doubleDFS(BinaryTreeNode<int>* left, BinaryTreeNode<int>* right) {
    if(left == nullptr && right == nullptr) return true;
    else if(left == nullptr || right == nullptr || (left->data != right->data)) return false;
    else if(doubleDFS(left->left.get(), right->right.get()) && doubleDFS(left->right.get(), right->left.get())) return true;

    return false;
}

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
  else if(tree->left.get() == nullptr && tree->right.get() == nullptr) return true;
  else if(doubleDFS(tree->left.get(), tree->right.get()) == true) return true;
  else return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
