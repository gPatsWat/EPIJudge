#include <string>

#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string &expression) {
  std::stringstream ss(expression);
  string token;
  char delim = ',';
  std::stack<int> st;

  while (getline(ss, token, delim)) {
    if (token == "+" || token == "-" || token == "/" || token == "*") {
      int b = st.top();
      st.pop();
      int a = st.top();
      st.pop();
      if (token == "+") {
        st.push(a + b);
      } else if (token == "-") {
        st.push(a - b);
      } else if (token == "/") {
        st.push(a / b);
      } else if (token == "*") {
        st.push(a * b);
      }
    } else {
      st.push(stoi(token));
    }
  }
  return st.top();
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
