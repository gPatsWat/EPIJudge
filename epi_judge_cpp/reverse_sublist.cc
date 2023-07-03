#include "list_node.h"
#include "test_framework/generic_test.h"
#include <cstddef>
#include <memory>

shared_ptr<ListNode<int>> foo(shared_ptr<ListNode<int>> s, shared_ptr<ListNode<int>> t) {
  if(s == t) return s;
  shared_ptr<ListNode<int>> rev_tail = foo(s->next, t);
  rev_tail->next = s;
  return s;
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if(L == nullptr) return nullptr;
  if(L->next == nullptr) return L;
  if(start == finish) return L;
  shared_ptr<ListNode<int>> s, sd, t, td, iter = L;
  bool is_start = start == 1;
  bool is_end;

  for(int i = 1;i<finish;i++) {
    if(i == start-1) sd = iter;
    if(i == start) s = iter;
    iter = iter->next;
  }

  is_end = iter->next == nullptr;
  td = iter->next;

  foo(s, t);

  if(!is_end) {
    s->next = td;
  }
  else s->next = nullptr;

  if(is_start) return t;
  else {
    sd->next = t;
    return L;
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
