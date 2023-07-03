#include <stdexcept>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;
class Queue {
  std::stack<int> s1, s2;
  bool enqueue = false;
 public:
  void Enqueue(int x) {
    if(!enqueue) {
      swap_stack(s1, s2);
      enqueue = true;
    }
    s1.push(x);    
    return;
  }
  int Dequeue() {
    if(enqueue) {
      swap_stack(s1, s2);
      enqueue = false;
    }
    int temp = s2.top();
    s2.pop();
    return temp;
  }

  void swap_stack(std::stack<int>& s1, std::stack<int>& s2) {
    if(s1.empty()) {
      while(!s2.empty()) {
        int temp = s2.top();
        s2.pop();
        s1.push(temp);
      }
    }
    else if(s2.empty()) {
      while(!s1.empty()) {
        int temp = s1.top();
        s1.pop();
        s2.push(temp);
      }
    }
  }
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  try {
    Queue q;
    for (auto& x : ops) {
      switch (x.op) {
        case QueueOp::Operation::kConstruct:
          break;
        case QueueOp::Operation::kDequeue: {
          int result = q.Dequeue();
          if (result != x.argument) {
            throw TestFailure("Dequeue: expected " +
                              std::to_string(x.argument) + ", got " +
                              std::to_string(result));
          }
        } break;
        case QueueOp::Operation::kEnqueue:
          q.Enqueue(x.argument);
          break;
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "queue_from_stacks.cc", "queue_from_stacks.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
