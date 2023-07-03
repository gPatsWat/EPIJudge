#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void ApplyPermutationwithOnspace(vector<int> perm, vector<int> *A_ptr) {
  vector<int> newvec((*A_ptr).size(), 0);
  for (int i = 0; i < (*A_ptr).size(); i++) {
    newvec[perm[i]] = (*A_ptr)[i];
  }
  (*A_ptr).clear();
  (*A_ptr).assign(newvec.begin(), newvec.end());
  return;
}

void ApplyPermutation(vector<int> perm, vector<int> *A_ptr) {
  int temp = 0, temp2 = 0, tindex = 0, tindex2 = 0, start = 0;

  for (int i = 0; i < (*A_ptr).size(); i++) {
    temp = (*A_ptr)[i];
    tindex = perm[i];
    while (perm[tindex] != tindex) {
      tindex2 = perm[tindex];
      temp2 = (*A_ptr)[tindex];

      (*A_ptr)[tindex] = temp;
      perm[tindex] = tindex;

      tindex = tindex2;
      temp = temp2;
    }
  }

  return;
}

vector<int> ApplyPermutationWrapper(const vector<int> &perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
