#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void adj_carry(vector<int>& ans) {
  int max_digit = 0;
  for(int i = 0;i<ans.size()-1;i++) {
    if(ans[i]/10 > 0) {
      ans[i+1] += ans[i]/10;
      ans[i] %= 10;
    }
  }

  for(int i = ans.size()-1;i>=0;i--) {
    if(ans[i] != 0) {
      ans.resize(i+1);
      break;
    }
  }

}

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  vector<int> ans(num1.size() + num2.size(), 0);

  if(num1.size() == 1 && ((num1[0] == 0) || (num1[0] == -0))) return {0};
  if(num2.size() == 1 && ((num2[0] == 0) || (num2[0] == -0))) return {0};

  bool neg1 = num1[0] < 0?true:false;
  bool neg2 = num2[0] < 0?true:false;
  num1[0] = neg1?-num1[0]:num1[0];
  num2[0] = neg2?-num2[0]:num2[0];
  std::reverse(num1.begin(), num1.end());
  std::reverse(num2.begin(), num2.end());

  for(int i = 0;i < num1.size();i++) {
    for(int j = 0;j < num2.size();j++) {
      ans[i+j] += num1[i]*num2[j];
    }
  }

  adj_carry(ans);

  std::reverse(ans.begin(), ans.end());

  if(neg1^neg2)ans[0] = -ans[0];

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};

  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
