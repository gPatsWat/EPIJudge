#include <string>

#include "test_framework/generic_test.h"
using std::string;
int RomanToInteger(const string& s) {
  int result = 0;
  int i = 0;
  while(i < s.size()) {
    switch (s[i]) {
      case 'I':
      result += 1;
      break;
      case 'V':
      if(i>0 && s[i-1] == 'I')
      result += 3;
      else result += 5;
      break;
      case 'X':
      if(i>0 && s[i-1] == 'I')
      result += 8;
      else result += 10;
      break;
      case 'L': //50
      if(i>0 && s[i-1] == 'X')
      result += 30;
      else result += 50;
      break;
      case 'C': //100
      if(i>0 && s[i-1] == 'X')
      result += 80;
      else result += 100;
      break;
      case 'D': //500
      if(i>0 && s[i-1] == 'C')
      result += 300;
      else result += 500;
      break;
      case 'M': //1000
      if(i>0 && s[i-1] == 'C')
      result += 800;
      else result += 1000;
      break;
    }
    i++;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
