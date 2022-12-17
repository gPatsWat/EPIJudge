#include <tuple>
#include <algorithm>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;
};

Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
  Rect xless, xmore, yless, ymore;

  if(r1.x <= r2.x) {
    xless = r1;
    xmore = r2;
  }
  else {
    xless = r2;
    xmore = r1;
  }

  if(r1.y <= r2.y) {
    yless = r1;
    ymore = r2;
  }
  else {
    yless = r2;
    ymore = r1;
  }

  if((xless.x + xless.width < xmore.x) || (yless.y + yless.height < ymore.y))
    return {0, 0, -1, -1};

  return {xmore.x,
          ymore.y,
          xmore.x + xmore.width < xless.x + xless.width? xmore.width:abs(xless.x + xless.width - xmore.x),
          ymore.y + ymore.height < yless.y + yless.height? ymore.height:abs(yless.y + yless.height - ymore.y)};
}
bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework {
template <>
struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("height({})", arg_name), FmtStr("width({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height, x.width};
  }
};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"r1", "r2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
