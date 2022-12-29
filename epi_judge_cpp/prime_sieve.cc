#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  vector<int> sol;
  vector<bool> sieve(n+1, false);
  for(int i=2;i < n+1;i++) {
    int t = i;
    if(sieve[t] == false) {
      sol.push_back(t);
      sieve[t] = true;
      int j = 2;
      while(t*j < n+1) {
        sieve[t*j] = true;
        j++;
      }
    }
  }
  return sol;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
