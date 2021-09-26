#ifndef ALDOUSBRODERMAZE_H
#define ALDOUSBRODERMAZE_H

#include "maze.h"

struct aldous_cell {
  bool visited = false;
  int x;
  int y;
};

class AldousBroderMaze : public Maze<aldous_cell> {
 public:
  AldousBroderMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze(renderer, window_width, window_height, width, height, scale) {}

  void init() override;
  void reset() override;
  bool iterate() override;

 private:
  aldous_cell* current_cell;
  int visited_count = 0;

  void connect(aldous_cell* c1, aldous_cell* c2);
  aldous_cell* get_random_neighbor(aldous_cell* cell);
  void set_visited(aldous_cell* cell);
  bool is_visited(aldous_cell* cell);
  bool are_unvisited_cells();
  void set_x(int x, int y, int newx);
  void set_y(int x, int y, int newy);
};

#endif