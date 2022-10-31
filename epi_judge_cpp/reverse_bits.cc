#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  unsigned long long rev = 0;
  for(int i = 0;i<64;i++) {
    rev <<= 1;
    rev |= x & 0x0000000000000001;
    x >>= 1;
  }
  return rev;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
