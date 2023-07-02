#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  std::unordered_map<char, int> mp;

  for(auto ch : magazine_text) {
    if(mp.find(ch) != mp.end()) {
      mp[ch]++;
    }
    else mp[ch] = 1;
  }

  for(auto ch : letter_text) {
    if(mp.find(ch) != mp.end()) {
      mp[ch]--;
      if(mp[ch] < 0) return false;
    }
    else return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
