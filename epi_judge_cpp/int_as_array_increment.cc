#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int sz = A.size()-1, i = sz;
  while(A[i] == 9) {
    A[i] = 0;
    if(i == 0) {
        A.insert(A.begin(), 0);
        break;
    }
    else i--;
  }
    A[i]++;
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
