#include <bits/stdc++.h>
#include "test_framework/generic_test.h"

uint8_t arr[2<<8] = {0};

short CountBits_only_bits(unsigned int x)
{
  int parity = 0;
  while (x)
  {
    x = x & (x - 1);
    parity++;
  }
  return parity;
}

short CountBits_hash(unsigned int x) {
  short parity = 0;
  for(int i = 0;i<8;i++) {
    uint8_t y = 0x00000000000000ff & x;
    x = x>>8;
    parity += arr[y];
  }
  return parity;
}

short CountBits(unsigned int x)
{
  return CountBits_hash(x);
}

int main(int argc, char *argv[])
{
  for(int i = 0;i<256;i++) {
    arr[i] = CountBits_only_bits(i);
  }

  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}
