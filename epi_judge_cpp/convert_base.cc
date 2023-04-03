#include <algorithm>
#include <string>

#include "test_framework/generic_test.h"
using std::string;

/*
  not considering negative numbers
  1. convert to int then to base b2 (can lead to integer overflow)
  2. convert to base 2 (string form) then to base b2 (string form)
*/

int convert_int(const string &num_as_string, int b1) {
  int acc = 0;
  string s(num_as_string);
  std::reverse(s.begin(), s.end());
  for (int i = 0; i < num_as_string.size(); i++) {
    if (s[i] >= 'A') {
      acc += (10 + s[i] - 'A') * pow(b1, i);
    } else {
      acc += (s[i] - '0') * pow(b1, i);
    }
  }
  return acc;
}

string ConvertBase(const string &num_as_string, int b1, int b2) {
  bool neg = false;
  if(num_as_string.size() == 1 && num_as_string[0] == '0') return "0";
  if(num_as_string[0] == '-') neg = true;
  int base_ten = 0, digit = 0;
  if(neg) base_ten = convert_int(num_as_string.substr(1), b1);
  else base_ten = convert_int(num_as_string, b1);
  string s;
  if(neg) s.push_back('-');
  while (base_ten > 0) {
    digit = base_ten % b2;
    if(digit >= 10)
      s.push_back(digit-10+'A');
    else
      s.push_back(digit+'0');
    base_ten /= b2;
  }
  if(neg)std::reverse(s.begin()+1, s.end());
  else std::reverse(s.begin(), s.end());
  return s;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
