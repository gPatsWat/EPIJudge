#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  shared_ptr<ListNode<int>> p1 = L, p2, s1, s2;
  if(L == nullptr) return L;
  p2 = L->next;
  s1 = L;
  s2 = L->next;

  while(p1 != nullptr && p2 != nullptr && p1->next != nullptr && p2->next != nullptr) {
    p1->next = p2->next;
    p1 = p1->next;
    p2->next = p1->next;
    p2 = p2->next;
  }

  p1->next = s2;

  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
