#include <cctype>
#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  if(s.size() <= 1) return true;
  string punc = ",.! '\";(){}[]@/&=><?#|^_\\-";
  int i = 0,j = s.size()-1;
  while(i<=j) {
    if(punc.find(s[i]) != string::npos) {
      i++;
      continue;
    }
    if(punc.find(s[j]) != string::npos) {
      j--;
      continue;
    }
    if(tolower(s[i]) != tolower(s[j])) {
      return false;
    }
    else {
      i++;
      j--;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
