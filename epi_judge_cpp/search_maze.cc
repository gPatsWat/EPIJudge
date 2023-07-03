#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kWhite, kBlack };
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

vector<std::pair<int, int>> dir = {{-1,0},{0,-1},{0,1},{1,0}};

bool isvalid(vector<vector<Color>> maze, int x, int y) {
  if((0 <= x) && (x < maze.size()) && (0 <= y) && (y < maze[0].size())) return true;
  return false;
}

bool dfs(vector<vector<Color>>& maze, const Coordinate& s, const Coordinate& e,
vector<Coordinate>& path, vector<vector<bool>>& vis) {
  path.push_back(s);
  if(vis[s.x][s.y]) {
    path.pop_back();
    return false;
  }
  
  if(s == e) return true;


  vis[s.x][s.y] = true;

  for(auto i : dir) {
      if(!(i.first == 0 && i.second == 0) && isvalid(maze, s.x + i.first, s.y + i.second) && (maze[s.x + i.first][s.y + i.second] == Color::kWhite) && dfs(maze, {s.x + i.first, s.y + i.second}, e, path, vis)) return true;
  }

  path.pop_back();
  return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
  vector<Coordinate> path;
  vector<vector<bool>> vis(maze.size(), vector<bool> (maze[0].size(), false));
  if((maze.size() == 0) || (maze[0].size() == 0) || !isvalid(maze, s.x, s.y)
   || !isvalid(maze, e.x, e.y) || (maze[s.x][s.y] == Color::kBlack) 
   || (maze[e.x][e.y] == Color::kBlack)) {
    return {};
   }
  if(dfs(maze, s, e, path, vis)) return path;
  return {};
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
