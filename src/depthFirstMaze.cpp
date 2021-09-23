#include "depthFirstMaze.h"

void DepthFirstMaze::init() {
  for (int x = 0; x < width(); ++x) {
    for (int y = 0; y < height(); ++y) {
      point(x, y, wall_color[0], wall_color[1], wall_color[2]);
    }
  }

  for (int x = 0; x < maze_width; ++x) {
    for (int y = 0; y < maze_height; ++y) {
      set_x(x, y, x);
      set_y(x, y, y);
      set_visited(x, y, false);
    }
  }

  auto* cell = push_cell(maze_width / 2, maze_height / 2);
  cell->visited = true;
}

void DepthFirstMaze::reset() {
    cell_stack = std::stack<depth_first_cell*>(); //clear stack
}

bool DepthFirstMaze::iterate() {
  if (cell_stack.empty()) return false;

  auto* top_cell = cell_stack.top();
  cell_stack.pop();

  point((top_cell->x * 2 + 1), (top_cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);

  auto neighbors = get_unvisited_neighbors(top_cell);
  if (!neighbors.empty()) {
    cell_stack.push(top_cell);
    auto* rand_cell = get_random_neighbor(neighbors);
    connect(top_cell, rand_cell);
    rand_cell->visited = true;
    push_cell(rand_cell);
  }

  return true;
}

std::vector<depth_first_cell*> DepthFirstMaze::get_unvisited_neighbors(depth_first_cell* c) {
  std::vector<depth_first_cell*> ret;

  if ((c->x - 1 >= 0)) {
    if (!get_is_visited((c->x - 1), c->y)) {
      push_back_cell(ret, c->x - 1, c->y);
    }
  }
  if ((c->y - 1 >= 0)) {
    if (!get_is_visited(c->x, (c->y - 1))) {
      push_back_cell(ret, c->x, c->y - 1);
    }
  }
  if ((c->x + 1 < maze_width)) {
    if (!get_is_visited((c->x + 1), c->y)) {
      push_back_cell(ret, c->x + 1, c->y);
    }
  }
  if ((c->y + 1 < maze_height)) {
    if (!get_is_visited(c->x, (c->y + 1))) {
      push_back_cell(ret, c->x, c->y + 1);
    }
  }

  return ret;
}

void DepthFirstMaze::connect(depth_first_cell* c1, depth_first_cell* c2) {
  int x_diff = c1->x - c2->x;
  int y_diff = c1->y - c2->y;
  if (x_diff == 0 && y_diff > 0) {
    point((c1->x * 2 + 1), (c1->y * 2), path_color[0], path_color[1], path_color[2]);
  } else if (x_diff == 0 && y_diff < 0) {
    point((c1->x * 2 + 1), (c1->y * 2 + 2), path_color[0], path_color[1], path_color[2]);
  } else if (y_diff == 0 && x_diff > 0) {
    point((c1->x * 2), (c1->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
  } else if (y_diff == 0 && x_diff < 0) {
    point((c1->x * 2 + 2), (c1->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
  }
}

depth_first_cell* DepthFirstMaze::get_random_neighbor(const std::vector<depth_first_cell*>& neighbors) {
  assert(neighbors.size() > 0);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, neighbors.size() - 1);
  return neighbors[dist(rng)];
}

depth_first_cell* DepthFirstMaze::push_cell(int x, int y) {
  auto* cell = &maze.get()[y * maze_width + x];
  cell_stack.push(cell);
  return cell;
}

inline void DepthFirstMaze::push_back_cell(std::vector<depth_first_cell*>& cells, int x, int y) {
  cells.push_back(&maze.get()[y * maze_width + x]);
}

inline void DepthFirstMaze::push_cell(depth_first_cell* cell) {
  cell_stack.push(cell);
}

inline void DepthFirstMaze::set_x(int x, int y, int newx) {
  maze.get()[y * maze_width + x].x = newx;
}

inline void DepthFirstMaze::set_y(int x, int y, int newy) {
  maze.get()[y * maze_width + x].y = newy;
}

inline void DepthFirstMaze::set_visited(int x, int y, bool v) {
  maze.get()[y * maze_width + x].visited = v;
}

inline bool DepthFirstMaze::get_is_visited(int x, int y) {
  return maze.get()[y * maze_width + x].visited;
}