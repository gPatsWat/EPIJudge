#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

std::map<char,string> keypad = {{'0', "0"},{'1', "1"},{'2', "ABC"},{'3', "DEF"},{'4', "GHI"},{'5', "JKL"},{'6', "MNO"}, \
{'7',"PQRS"}, {'8', "TUV"}, {'9', "WXYZ"}, {'*', "*"}, {'0', "0"}, {'#', "#"}};

void foo(string& mnemonic, vector<string>& str, const string& phone_number, int i) {
  if(i == phone_number.size()) {
    // std::cout << mnemonic << std::endl;
    str.push_back(mnemonic);
    return;
  }

  for(int j = 0;j < keypad[phone_number[i]].size();j++) {
    mnemonic += keypad[phone_number[i]][j];
    foo(mnemonic, str, phone_number, i+1);
    mnemonic.erase(mnemonic.size()-1);
  }
}

vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> str;
  string mnemonic = "";
  foo(mnemonic, str, phone_number, 0);
  std::cout << str[0] << std::endl;
  return str;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
