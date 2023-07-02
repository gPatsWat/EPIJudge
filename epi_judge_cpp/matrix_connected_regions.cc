#include <deque>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

bool isvalid(vector<deque<bool>>* image_ptr, int x, int y) {
  if(x >= 0 && x < image_ptr[0].size() && y >= 0 && y < image_ptr->size()) return true;
  return false;
}

void bfs(int x, int y, vector<deque<bool>>* image_ptr) {
  std::queue<std::pair<int, int>> q;
  vector<std::pair<int,int>> dir = {{-1,0},{1,0},{0,1},{0,-1}};
  bool initial_color = (*image_ptr)[x].at(y);
  bool flip_color = !initial_color;
  q.push({x, y});

  while(!q.empty()) {
    auto top = q.front();
    q.pop();
    (*image_ptr)[top.first][top.second] = flip_color;

    for(auto i : dir) {
      if(isvalid(image_ptr, top.first + i.first, top.second + i.second) && (*image_ptr)[top.first + i.first][top.second + i.second] == initial_color)
        q.push({top.first + i.first, top.second + i.second});
    }
  }
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  if(image_ptr == nullptr) return;
  bfs(x, y, image_ptr);
  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
