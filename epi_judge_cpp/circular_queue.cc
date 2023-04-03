#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <algorithm>

class Queue {
 public:
  int head,tail,num;
  std::vector<int> v;

  Queue(size_t capacity) {
    head = 0;
    tail = 0;
    num = 0;
    v.resize(capacity);
  }

  bool isEmpty() {
    if(num == 0) {
      return true;
    }
    return false;
  }

  bool isFull() {
    if(num == v.size()) {
      return true;
    }
    return false;
  }

  void Enqueue(int x) {
    v[tail] = x;
    num++;
    if(isFull()) {
        std::rotate(v.begin(), v.begin()+head, v.end());
        head = 0;
        tail = v.size()-1;
        v.resize(v.size()*2);
    }
    tail = (tail+1)%v.size();
    return;
  }

  int Dequeue() {
    if(isEmpty()) {
      throw std::length_error("empty queue");
    }
    int temp = v[head];
    head = (head+1)%v.size();
    num--;
    return temp;
  }

  int Size() const {
    return num;
  }
};

struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
