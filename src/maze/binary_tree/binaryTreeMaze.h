#ifndef BINARYTREEMAZE_H
#define BINARYTREEMAZE_H

#include "maze.h"

struct binary_cell {};

class BinaryTreeMaze : public Maze<binary_cell> {
 public:
  BinaryTreeMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze(renderer, window_width, window_height, width, height, scale), rng(dev()), dist(0, 1) {}

  void init() override;
  void reset() override;
  bool iterate() override;

 private:
  int current_x = 0;
  int current_y = 0;
  std::random_device dev;
  std::mt19937 rng;
  std::uniform_int_distribution<std::mt19937::result_type> dist;

  void connect_left_or_up(int x, int y);
  void connect(int x1, int y1, int x2, int y2);
};

#endif