#include "kruskalMaze.h"

void KruskalMaze::init() {
  //put edge in edge_set
  int index = 0;
  for (int x = 0; x < maze_width; ++x) {
    for (int y = 0; y < maze_height; ++y) {
      if (x > 0) edge_set.push_back({x, y, false});
      if (y > 0) edge_set.push_back({x, y, true});
      int id = index++;
      maze[x * maze_height + y].id = id;
      maze[x * maze_height + y].cell_set.push_back(id);
    }
  }
  std::random_device dev;
  std::mt19937 rng(dev());

  std::shuffle(std::begin(edge_set), std::end(edge_set), rng);

  for (int x = 0; x < width(); ++x) {
    for (int y = 0; y < height(); ++y) {
      point(x, y, wall_color[0], wall_color[1], wall_color[2]);
    }
  }
}
void KruskalMaze::reset() {
}
bool KruskalMaze::iterate() {
  if (edge_set.empty()) return false;

  auto edge = edge_set.back();
  edge_set.pop_back();

  if (edge.direction) {  //up

    auto& set1 = maze[edge.x * maze_height + edge.y].cell_set;
    auto& set2 = maze[(edge.x - 1) * maze_height + (edge.y)].cell_set;

    for (int x = 0; x < maze_width; ++x) {
      for (int y = 0; y < maze_height; ++y) {

        // if()

        maze[(edge.x - 1) * maze_height + (edge.y)].id = 5;

      }
    }

    // if (is_distinct_set(edge.x, edge.y, edge.x - 1, edge.y)) {
    //   point((edge.x * 2 - 1), (edge.y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    //   point((edge.x * 2), (edge.y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    //   point((edge.x * 2 + 1), (edge.y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    //   connect(edge.x, edge.y, edge.x - 1, edge.y);
    // }

  } else {  //left

    // if (is_distinct_set(edge.x, edge.y, edge.x, edge.y - 1)) {
    //   point((edge.x * 2 + 1), (edge.y * 2 - 1), path_color[0], path_color[1], path_color[2]);
    //   point((edge.x * 2 + 1), (edge.y * 2), path_color[0], path_color[1], path_color[2]);
    //   point((edge.x * 2 + 1), (edge.y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    //   connect(edge.x, edge.y, edge.x, edge.y - 1);
    // }
  }

  return true;
}