#include "huntAndKillMaze.h"

void HuntAndKillMaze::init() {
  for (int x = 0; x < maze_width; ++x) {
    for (int y = 0; y < maze_height; ++y) {
      set_x(x, y, x);
      set_y(x, y, y);
      set_visited(x, y, false);
    }
  }

  for (int x = 0; x < width(); ++x) {
    for (int y = 0; y < height(); ++y) {
      point(x, y, wall_color[0], wall_color[1], wall_color[2]);
    }
  }

  current_cell = get_cell(maze_width / 2, maze_height / 2);
}
void HuntAndKillMaze::reset() {
}
bool HuntAndKillMaze::iterate() {
	point((current_cell->x * 2 + 1), (current_cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
  if (hunting) {
    auto opt_cell = hunt();

    if (!opt_cell) return false;

    current_cell = opt_cell.value();
    hunting = false;
  }

  current_cell->visited = true;

  auto neighbors = get_unvisited_neighbors(current_cell);

  if (neighbors.empty()) {
    hunting = true;
    return true;
  }

  auto* rand_cell = get_random_neighbor(neighbors);


  connect(current_cell, rand_cell);

  current_cell = rand_cell;

  return true;
}

std::vector<hunt_and_kill_cell*> HuntAndKillMaze::get_visited_neighbors(hunt_and_kill_cell* c) {
  std::vector<hunt_and_kill_cell*> ret;

  if ((c->x - 1 >= 0)) {
    if (get_is_visited((c->x - 1), c->y)) {
      push_back_cell(ret, c->x - 1, c->y);
    }
  }
  if ((c->y - 1 >= 0)) {
    if (get_is_visited(c->x, (c->y - 1))) {
      push_back_cell(ret, c->x, c->y - 1);
    }
  }
  if ((c->x + 1 < maze_height)) {
    if (get_is_visited((c->x + 1), c->y)) {
      push_back_cell(ret, c->x + 1, c->y);
    }
  }
  if ((c->y + 1 < maze_width)) {
    if (get_is_visited(c->x, (c->y + 1))) {
      push_back_cell(ret, c->x, c->y + 1);
    }
  }

  return ret;
}

std::vector<hunt_and_kill_cell*> HuntAndKillMaze::get_unvisited_neighbors(hunt_and_kill_cell* c) {
  std::vector<hunt_and_kill_cell*> ret;

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

void HuntAndKillMaze::connect(hunt_and_kill_cell* c1, hunt_and_kill_cell* c2) {
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

hunt_and_kill_cell* HuntAndKillMaze::get_random_neighbor(const std::vector<hunt_and_kill_cell*>& neighbors) {
  assert(neighbors.size() > 0);
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, neighbors.size() - 1);
  return neighbors[dist(rng)];
}

inline void HuntAndKillMaze::push_back_cell(std::vector<hunt_and_kill_cell*>& cells, int x, int y) {
  cells.push_back(&maze.get()[y * maze_width + x]);
}

inline void HuntAndKillMaze::set_x(int x, int y, int newx) {
  maze.get()[y * maze_width + x].x = newx;
}

inline void HuntAndKillMaze::set_y(int x, int y, int newy) {
  maze.get()[y * maze_width + x].y = newy;
}

inline void HuntAndKillMaze::set_visited(int x, int y, bool v) {
  maze.get()[y * maze_width + x].visited = v;
}

inline bool HuntAndKillMaze::get_is_visited(int x, int y) {
  return maze.get()[y * maze_width + x].visited;
}

std::optional<hunt_and_kill_cell*> HuntAndKillMaze::hunt() {
  for (int x = 0; x < maze_width; ++x) {
    for (int y = 0; y < maze_height; ++y) {
      if (!get_is_visited(x, y)) {  // if unvisited cell
        //find unvisited neighbor
        auto neighbors = get_visited_neighbors(get_cell(x, y));
        if (neighbors.empty()) continue;
        return get_random_neighbor(neighbors);
      }
    }
  }
  return std::nullopt;
}