#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string& s) {
  std::unordered_map<char, int> hmp;
  for(auto ch : s) {
    if(hmp.find(ch) != hmp.end()) {
      hmp[ch]++;
    }
    else hmp[ch] = 1;
  }

  bool is_one_odd = false;
  bool is_all_even = true;
  for(auto iter = hmp.begin(); iter != hmp.end();iter++) {
    if(iter->second%2 && is_one_odd)
      return false;
    else if(iter->second%2) {
      is_one_odd = true;
      is_all_even = false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
