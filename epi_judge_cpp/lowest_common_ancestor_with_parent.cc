#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <cstddef>

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  if(node0.get() == nullptr || node1.get() == nullptr) return nullptr;
  std::vector<BinaryTreeNode<int>*> a, b;
  BinaryTreeNode<int>* iter = node0.get();
  while (iter != nullptr) {
    a.push_back(iter);
    iter = iter->parent;
  }

  iter = node1.get();

  while (iter != nullptr) {
    b.push_back(iter);
    iter = iter->parent;
  }

  for(int i = a.size()-1, j = b.size()-1;(i >= 0) && (j >= 0);i--,j--) {
    if((i == 0) && (a[i] != b[j])) return a[i+1];
    else if((i == 0) && (a[i] == b[j])) return a[0];
    else if((j == 0) && (a[i] != b[j])) return b[j+1];
    else if((j == 0) && (a[i] == b[j])) return b[0];
    else if(a[i] != b[j]) return a[i+1];
  }

  return nullptr;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
