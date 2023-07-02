#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
  enum direction { down, up };

  if (tree.get() == nullptr)
    return {};

  vector<int> ans;

  auto iter = tree.get();
  BinaryTreeNode<int> *temp = nullptr;
  direction d = down;
  while (!(iter == nullptr)) {
    if (d == down) {
      while (iter->left.get() != nullptr) {
        iter = iter->left.get();
      }
      ans.push_back(iter->data);
      if (iter->right.get()) {
        iter = iter->right.get();
        continue; // do same thing all over
      } else {
        // child node which is already printed. now backtrack
        temp = iter;
        iter = iter->parent;
        d = up;
        continue;
      }
    } else {
      if (temp == iter->left.get()) {
        // coming from left
        ans.push_back(iter->data);
        if (iter->right.get()) {
          iter = iter->right.get();
          d = down;
          continue;
        } else {
          temp = iter;
          iter = iter->parent;
          continue;
        }
      } else if (temp == iter->right.get()) {
        temp = iter;
        iter = iter->parent;
        continue;
      }
    }
  }
  return ans;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc", "tree_with_parent_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
