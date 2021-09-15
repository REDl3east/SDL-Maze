#include "clingyWilsonMaze.h"

bool ClingyWilsonMaze::do_walking() {
  if (!did_set_new_start()) return false;

  point((current_x * 2 + 1), (current_y * 2 + 1), walking_color[0], walking_color[1], walking_color[2]);

  auto visited_cell_opt = find_visited_cell(current_x, current_y);
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