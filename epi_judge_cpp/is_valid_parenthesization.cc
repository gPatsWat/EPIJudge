#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  int i = 0;
  std::stack<char> st;
  if(s == "") return true;

  while(i != s.size()) {
    if(s[i] == '(' || s[i] == '[' || s[i] == '{') {
      st.push(s[i]);
    }
    else if(s[i] == ')' || s[i] == ']' || s[i] == '}') {
      if(s[i] == ')' && !st.empty() && st.top() == '(') st.pop();
      else if(s[i] == ']' && !st.empty() && st.top() == '[') st.pop();
      else if(s[i] == '}' && !st.empty() && st.top() == '{') st.pop();
      else return false;
    }
    i++;
  }
  if(!st.empty()) return false;
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
