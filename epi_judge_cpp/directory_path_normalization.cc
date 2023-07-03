#include <string>
#include <sstream>

#include "test_framework/generic_test.h"
using std::string;

string ShortestEquivalentPath(const string& path) {
    if (path.empty()) return "";
  if (path == "..") return "..";
  if (path == ".") return ".";

  bool starts_root = false;
  if (path[0] == '/') starts_root = true;

  string token;
  std::stringstream ss(path);
  char delim = '/';

  std::deque<string> st;

  while (std::getline(ss, token, delim)) {
    if (token == "") {
      continue;
    } else if (token == ".") {
      continue;
    } else if (token == "..") {
      if (st.empty() || st.front() == "..") {
        st.push_back(token);
      }
      else st.pop_front();
    }
    else {
      st.push_front(token);
    }

  }

  string retval = "";
  if (starts_root) retval = "/";

  while(!st.empty()) {
    retval += st.back();
    st.pop_back();
    retval += "/";
  }

  if (retval.size() > 1)
    retval.erase(retval.size()-1);
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}