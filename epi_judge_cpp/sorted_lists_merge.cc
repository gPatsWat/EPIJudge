#include "list_node.h"
#include "test_framework/generic_test.h"
#include <cstddef>
#include <memory>
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  if(L1 == nullptr) return L2;
  if(L2 == nullptr) return L1;

  shared_ptr<ListNode<int>> a (L1->data < L2->data?L1:L2),b (L1->data < L2->data? L2:L1);

  while (a != nullptr && b != nullptr) {
    if (a->next != nullptr) {
      if (a->data <= b->data && a->next->data >= b->data) {
        shared_ptr<ListNode<int>> temp(a->next);
        a->next = b;
        b = b->next;
        a->next->next = temp;
      }
      else a = a->next;
    }
    else {
      a->next = b;
      break;
    }
  }

  if(L1->data < L2->data) {
    return L1;
  }
  else {
    return L2;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
