#include <memory>
#include <utility>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::pair;
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
      BinaryTreeNode<int>* nd = tree.get();
      if(nd == nullptr) return {};
      pair<BinaryTreeNode<int>*,int> p = {nd, 0};

      std::queue<pair<BinaryTreeNode<int>*, int>> q;
      q.push(p);
      int curdepth = 0;
      
      vector<vector<int>> v;
      while(!q.empty()) {
        vector<int> curv;
        while(!q.empty() && q.front().second == curdepth) {
          auto pnew = q.front();
          curv.push_back(pnew.first->data);
          if(pnew.first->left) q.push({pnew.first->left.get(), curdepth+1});
          if(pnew.first->right) q.push({pnew.first->right.get(), curdepth+1});
          q.pop();
        }
        v.push_back(curv);
        curdepth++;
      }
      
  return v;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
