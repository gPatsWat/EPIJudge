#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if(L == nullptr) return L;
  if(start >= finish) return L;

  shared_ptr<ListNode<int>> st = L, nd = L, st2 = nullptr, nd2 = nullptr, iter = nullptr, prev = nullptr, temp = nullptr;
  for(int i = 1;i < start;i++) {
    if(i == start-1) st2 = st;
    st = st->next;
  }
  for(int i = 1;(i < finish) && (nd->next != nullptr);i++) {
    nd = nd->next;
  }

  nd2 = nd->next;
  iter = st;

  prev = nd2;
  temp = iter->next;
  // std::cout << "nd2 data: " << nd2->data << "\n";
  while(iter != nd2) {
    iter->next = prev;
    prev = iter;
    iter = temp;
    if(temp != nullptr)
    temp = temp->next;
    else break;
  }

  if(start == 1) return nd;
  else st2->next = nd;

  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
