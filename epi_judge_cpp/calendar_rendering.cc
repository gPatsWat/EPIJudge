#include <limits>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event {
  int start, finish;
};
int FindMaxSimultaneousEvents(const vector<Event>& A) {
  std::vector<std::pair<int,bool>> points;
  vector<Event> ans(A.begin(), A.end());

  for(auto iter : ans) {
    points.push_back(std::make_pair(iter.start, true));
    points.push_back(std::make_pair(iter.finish, false));
  }

  std::sort(points.begin(), points.end(), [](std::pair<int, bool>& a, std::pair<int, bool>& b) {return a.first != b.first ? a.first < b.first : a.second && ! b.second; });

  int cnt = 0, maxval = std::numeric_limits<int>::min();

  for(auto i : points) {
    if(i.second == false) {
      cnt--;
    }
    else if(i.second == true) {
      cnt++;
      maxval = std::max(maxval, cnt);
    }
  }

  return maxval;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
