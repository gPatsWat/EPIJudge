#include "test_framework/generic_test.h"

double pow(double x, int y) {
  if(y == 1) return x;
  double z = pow(x, y/2);

  if(y%2 == 0) {
    return z*z;
  }
  else {
    return x*z*z;
  }
}

double Power(double x, int y) {
  bool invert = false;
  double ans;
  if(x==0)return 0.0;
  if(y == 0) return 1;
  if(y < 0) {
    y = -y;
    invert = true;
  }
  
  ans = pow(x,y);

  if(invert) return 1/ans;
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
