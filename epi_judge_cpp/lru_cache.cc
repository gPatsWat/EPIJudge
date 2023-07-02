#include <list>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
public:
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> hmp;
  // price, isbn
  std::list<std::pair<int, int>> lst;
  int _capacity;

  LruCache(size_t capacity) { _capacity = capacity; }

  int Lookup(int isbn) {
    if (hmp.find(isbn) != hmp.end()) {
      auto temp_price = *hmp[isbn];
      lst.erase(hmp[isbn]);
      lst.push_front(temp_price);
      hmp[isbn] = lst.begin();
      return temp_price.first;
    } else {
      return -1;
    }
    return 0;
  }

  void Insert(int isbn, int price) {
    int price_to_insert;
    if (hmp.find(isbn) != hmp.end()) {
      price_to_insert = (*hmp[isbn]).first;
      lst.erase(hmp[isbn]);
    } else {
      price_to_insert = price;
      if (_capacity == hmp.size()) {
        auto temp_price = lst.back();
        lst.pop_back();
        hmp.erase(temp_price.second);
      }
    }
    lst.push_front({price_to_insert, isbn});
    hmp[isbn] = lst.begin();
    return;
  }

  bool Erase(int isbn) {
    if (hmp.find(isbn) == hmp.end())
      return false;
    lst.erase(hmp[isbn]);
    hmp.erase(isbn);
    return true;
  }
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
} // namespace test_framework

void LruCacheTester(const std::vector<Op> &commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto &cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
