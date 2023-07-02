#include <algorithm>
#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

unique_ptr<BinaryTreeNode<int>> makeTree(vector<int>& in, vector<int>& pre, int in_beg, int in_end, int pre_beg, int pre_end) {
  if(in_beg == in_end) return std::make_unique<BinaryTreeNode<int>>(in[in_beg], nullptr, nullptr);
  auto root_index = std::find(in.begin(), in.end(), pre[pre_beg]);
  int left_size = root_index - in.begin();
  auto root = std::make_unique<BinaryTreeNode<int>>(pre[pre_beg], makeTree(in, pre, 0, root_index - in.begin(), pre_beg+1, pre_beg+left_size), makeTree(in, pre, root_index-in_beg, int in_end, int pre_beg, int pre_end));
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {

  if(preorder.size() == 0) return nullptr;
  return makeTree(inorder, preorder);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
