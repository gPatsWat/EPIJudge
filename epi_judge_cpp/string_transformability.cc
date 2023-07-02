#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

bool isdiffone(string& src, string& dest) {
  if(src.size() != dest.size())return false;
  bool diff = false;
  for(int i = 0;i < src.size(); i++) {
    if(diff == false && src[i] != dest[i]) diff = true;
    else if(diff == true && src[i] != dest[i]) return false;
  }

  return true;
}

// void buildgraph(std::unordered_multimap<string, string>& graph, unordered_set<string>& D) {
//   for(auto i : D) {
//     for(auto j : D) {
//       if(isdiffone(i, j)) graph.insert({i, j});
//     }
//   }
// }

//NOTE: while this is correct, it is too slow. you don't actually need to
//create a graph in this case as you're using bfs. the dictionary will serve
//as set of unvisited nodes.

// int bfs(std::unordered_multimap<string, string>& graph, string s, string d) {
//   std::queue<std::pair<string, int>> q;
//   unordered_set<string> vis;
//   q.push({s, 0});
//   while(!q.empty()) {
//     auto nd = q.front();
//     // std::cout << "popped: " << nd.first << std::endl;
//     q.pop();
//     if(d == nd.first) return nd.second;

//     vis.insert(nd.first);
//     auto ret = graph.equal_range(nd.first);
//     for(auto i = ret.first; i != ret.second;++i) {
//       if(vis.find(i->second) == vis.end())
//         q.push({i->second, nd.second+1});
//     }
//   }
//   return -1;
// }

int bfs(unordered_set<string> D, string s, string d) {
  std::queue<std::pair<string, int>> q;

  q.push({s, 0});
  while(!q.empty()) {
    auto nd = q.front();
    D.erase(nd.first);
    q.pop();
    if(d == nd.first) return nd.second;

    //it is actually faster to manually compute all possible
    //edges i.e. make changes in one letter for the string
    for(int i = 0;i < nd.first.size();i++) {
      for(int j = 0;j < 26;j++) {
        string newstr = nd.first;
        newstr[i] = 'a' + j;
        if(D.find(newstr) != D.end()){
          q.push({newstr, nd.second+1});
          D.erase(newstr);
        }
      }
    }
  }
  return -1;
}

int TransformString(unordered_set<string> D, const string& s, const string& t) {
  if(!(s.size() > 0 && t.size() > 0))return -1;
  return bfs(D, s, t);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
