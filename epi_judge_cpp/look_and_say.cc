#include <string>
#include <limits.h>

#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  std::queue<int> q;
  string str = "";
  q.push(1);
  q.push(INT_MAX);
  for (int i = 0; i < n; i++) {
    int first = q.front(), count = 0;
    while(q.front() != INT_MAX) {
      if(q.front() == first) count++;
      else {
        //insert count
        q.push(count);
        //insert number
        q.push(first);
        first = q.front();
        count = 1;
      }

      if(i == n-1) str += std::to_string(q.front());
      q.pop();
    }
    q.push(count);
    q.push(first);
    q.push(INT_MAX);
    q.pop();
  }
  return str;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  std::cout << LookAndSay(1);
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
