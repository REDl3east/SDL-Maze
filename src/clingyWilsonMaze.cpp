#include "clingyWilsonMaze.h"

bool ClingyWilsonMaze::do_walking() {
  if (!did_set_new_start()) return false;

  point((current_x * 2 + 1), (current_y * 2 + 1), walking_color[0], walking_color[1], walking_color[2]);

  auto visited_cell_opt = find_visited_cell(current_x, current_y); //TODO: choose random vistite cell
  if (visited_cell_opt) {
    connect(visited_cell_opt.value(), walked_cells.back());
    walking = false;
    return true;
  }

  auto neighbors = get_unvisited_neighbors(current_x, current_y);
  if (has_no_neighbors(neighbors)) return true;

  set_cell_to_walk(get_random_neighbor(neighbors));
  return true;
}

std::optional<wilson_cell*> ClingyWilsonMaze::find_visited_cell(int x, int y) {
  std::vector<wilson_cell*> cells;
  if ((x - 1 >= 0)) {
    if (is_visited((x - 1), y)) {
      cells.push_back(get_cell(x - 1, y));
    }
  }
  if ((y - 1 >= 0)) {
    if (is_visited(x, (y - 1))) {
      cells.push_back(get_cell(x, y - 1));
    }
  }
  if ((x + 1 < maze_height)) {
    if (is_visited((x + 1), y)) {
      cells.push_back(get_cell(x + 1, y));
    }
  }
  if ((y + 1 < maze_width)) {
    if (is_visited(x, (y + 1))) {
      cells.push_back(get_cell(x, y + 1));
    }
  }

  if (cells.empty()) {
    return std::nullopt;
  }
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, cells.size() - 1);
  return cells[dist(rng)];
}