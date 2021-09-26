#include "aldousBroderMaze.h"

void AldousBroderMaze::init() {
  for (int x = 0; x < width(); ++x) {
    for (int y = 0; y < height(); ++y) {
      point(x, y, wall_color[0], wall_color[1], wall_color[2]);
    }
  }

  for (int x = 0; x < maze_width; ++x) {
    for (int y = 0; y < maze_height; ++y) {
      set_x(x, y, x);
      set_y(x, y, y);
    }
  }

  //set current cell to random
  std::random_device dev1;
  std::mt19937 rng1(dev1());
  std::uniform_int_distribution<std::mt19937::result_type> dist1(0, width());
  std::uniform_int_distribution<std::mt19937::result_type> dist2(0, height());

  int x = dist1(rng1);
  int y = dist2(rng1);

  current_cell = get_cell(x, y);
  set_visited(current_cell);
}

void AldousBroderMaze::reset() {
}

bool AldousBroderMaze::iterate() {
  if (are_unvisited_cells()) {
    point((current_cell->x * 2 + 1), (current_cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    return false;
  }

  point((current_cell->x * 2 + 1), (current_cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);

  auto neighbor = get_random_neighbor(current_cell);

  if (!is_visited(neighbor)) {
    connect(current_cell, neighbor);
    set_visited(neighbor);
  }

  current_cell = neighbor;

  point((neighbor->x * 2 + 1), (neighbor->y * 2 + 1), 255, 0, 255);

  return true;
}

void AldousBroderMaze::connect(aldous_cell* c1, aldous_cell* c2) {
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

aldous_cell* AldousBroderMaze::get_random_neighbor(aldous_cell* cell) {
  std::vector<aldous_cell*> cells;
  if ((cell->x - 1 >= 0)) {
    cells.push_back(get_cell(cell->x - 1, cell->y));
  }
  if ((cell->y - 1 >= 0)) {
    cells.push_back(get_cell(cell->x, cell->y - 1));
  }
  if ((cell->x + 1 < maze_width)) {
    cells.push_back(get_cell(cell->x + 1, cell->y));
  }
  if ((cell->y + 1 < maze_height)) {
    cells.push_back(get_cell(cell->x, cell->y + 1));
  }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, cells.size() - 1);
  return cells[dist(rng)];
}

void AldousBroderMaze::set_visited(aldous_cell* cell) {
  visited_count++;
  cell->visited = true;
}

bool AldousBroderMaze::is_visited(aldous_cell* cell) {
  return cell->visited;
}

bool AldousBroderMaze::are_unvisited_cells() {
  return visited_count >= maze_width * maze_height;
}

void AldousBroderMaze::set_x(int x, int y, int newx) {
  maze.get()[y * maze_width + x].x = newx;
}

void AldousBroderMaze::set_y(int x, int y, int newy) {
  maze.get()[y * maze_width + x].y = newy;
}