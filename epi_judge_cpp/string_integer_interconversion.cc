#include <algorithm>
#include <string>
#include <climits>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

//check overflow when x is negative. int takes -n to n-1
string IntToString(int x) {
  string s = "";
  bool int_min = false;
  if(x < 0) {
    if(x == INT_MIN) {
      int_min = true;
      x++;
    }
    x = -x;
    s.push_back('-');
  }

  if(x == 0) return "0";
  while(x != 0) {
    s.push_back((char)(x%10 + '0'));
    x /= 10;
  }
  if(int_min == true) s[1] += 1;
  if(s[0] == '-') std::reverse(s.begin()+1, s.end());
  else std::reverse(s.begin(), s.end());
  return s;
}

int StringToInt(const string& s) {
  int x = 0;
  bool neg = false;
  if(s.size() == 1 && s[0] == '0') return 0;
  for(int i = 0;i < s.size();i++) {
    if(s[i] == '-') neg = true;
    else if(s[i] == '+') {}
    else {
      x *= 10;
      x += s[i] - '0';
    }
  }
  if(neg) return -x;
  return x;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
