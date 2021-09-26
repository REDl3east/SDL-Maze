#include "binaryTreeMaze.h"

void BinaryTreeMaze::init() {
  for (int x = 0; x < width(); ++x) {
    for (int y = 0; y < height(); ++y) {
      point(x, y, wall_color[0], wall_color[1], wall_color[2]);
    }
  }
}

void BinaryTreeMaze::reset() {
}

bool BinaryTreeMaze::iterate() {
  point((current_x * 2 + 1), (current_y * 2 + 1), path_color[0], path_color[1], path_color[2]);
  connect_left_or_up(current_x, current_y);

  if (current_x >= maze_width - 1 && current_y >= maze_height - 1) return false;

  current_x++;
  if (current_x >= maze_width) {
    current_x = 0;
    current_y++;
  }

  return true;
}

void BinaryTreeMaze::connect_left_or_up(int x, int y) {
  if (x <= 0 && y <= 0) return;  // do nothing

  if (x <= 0) {  // go left
    connect(x, y, x, y - 1);
  } else if (y <= 0) {  // go up
    connect(x, y, x - 1, y);
  } else {
    int rand = dist(rng);
    if (rand == 0) {  // go left
      connect(x, y, x, y - 1);
    } else {  // go up
      connect(x, y, x - 1, y);
    }
  }
}

void BinaryTreeMaze::connect(int x1, int y1, int x2, int y2) {
  int x_diff = x1 - x2;
  int y_diff = y1 - y2;
  if (x_diff == 0 && y_diff > 0) {
    point((x1 * 2 + 1), (y1 * 2), path_color[0], path_color[1], path_color[2]);
  } else if (x_diff == 0 && y_diff < 0) {
    point((x1 * 2 + 1), (y1 * 2 + 2), path_color[0], path_color[1], path_color[2]);
  } else if (y_diff == 0 && x_diff > 0) {
    point((x1 * 2), (y1 * 2 + 1), path_color[0], path_color[1], path_color[2]);
  } else if (y_diff == 0 && x_diff < 0) {
    point((x1 * 2 + 2), (y1 * 2 + 1), path_color[0], path_color[1], path_color[2]);
  }
}