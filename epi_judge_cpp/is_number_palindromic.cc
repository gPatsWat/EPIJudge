#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  if(x == 0) return true;
  bool neg = x < 0?true:false;
  if(neg) return false;
  int rev = 0, oldx = x;

  while(x) {
    rev *= 10;
    rev += x%10;
    x /= 10;
  }

  if(rev == oldx)
    return true;
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
