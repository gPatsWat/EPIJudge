#include <cstddef>
#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.

//**** Inefficient solution, alternating till end***//
// shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
//                                         int k) {
//   if(L == nullptr) return nullptr;
//   shared_ptr<ListNode<int>> iter = nullptr, iter2 = L;
//   for(int i = 0;i < k;i++) {
//     while(iter2->next != iter) iter2 = iter2->next;
//     iter = iter2;
//     iter2 = L;
//   }
//   iter2 = L;
//   if(iter == L) {
//     iter = L->next;
//     L->next = nullptr;
//     return iter;
//   }
//   while(iter2->next != iter) iter2 = iter2->next;
//   iter2->next = iter->next;
//   // iter->next = nullptr;
//   return L;
// }

//efficient O(n) solution
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
     shared_ptr<ListNode<int>> ptr1, ptr2;
      if(L == nullptr) return nullptr;
      ptr1 = L;
      for(int i = 0;i < k;i++) {
        ptr1 = ptr1->next;
      }
      if(ptr1 == nullptr)return L->next;
      ptr2 = ptr1;
      ptr1 = L;
      while(ptr2->next != nullptr) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
      }

      ptr1->next = ptr1->next->next;
      return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
