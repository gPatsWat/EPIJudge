#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  int mindist = std::numeric_limits<int>::max();

  std::unordered_map<string, int> mp;
  for(int i = 0;i < paragraph.size();i++) {
    if(mp.find(paragraph[i]) == mp.end()) mp.insert({paragraph[i], i});
    else {
      mindist = std::min(mindist, i - mp[paragraph[i]]);
      mp.erase(paragraph[i]);
      mp.insert({paragraph[i], i});
    }
  }
  if(mindist == std::numeric_limits<int>::max()) return -1;
  return mindist;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
