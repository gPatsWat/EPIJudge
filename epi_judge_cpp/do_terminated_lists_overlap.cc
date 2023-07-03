#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  auto i = l0;
  auto j = l1;
  if(i == nullptr) return nullptr;
  if(j == nullptr) return nullptr;

  int n1 = 0, n2 = 0;
  while(i->next != nullptr) {
    n1++;
    // std::cout << "l1 iter" << std::endl;
    i = i->next;
  }

  while(j->next != nullptr) {
    n2++;
    // std::cout << "l2 iter" << std::endl;
    j = j->next;
  }

  if(i != j)  {
    // std::cout << "no match" << std::endl;
    return nullptr;
  }

  int diff = abs(n2 - n1), count = 0;
  std::cout << diff << std::endl;
  i = n1>n2?l0:l1;
  j = n1>n2?l1:l0;

  while(diff != 0) {
    i = i->next;
    diff--;
  }

  while(i != j) {
    i = i->next;
    j = j->next;
  }

  return i;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
