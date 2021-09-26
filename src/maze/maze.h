#ifndef MAZE_H
#define MAZE_H

#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <stack>

#include "pixelWorld.h"

template <typename Cell>
class Maze : public PixelWorld {
 public:
  Maze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : PixelWorld(renderer, window_width, window_height, width, height, scale) {
    if (width % 2 == 0) throw std::runtime_error("invalid arguments");
    if (height % 2 == 0) throw std::runtime_error("invalid arguments");

    maze_width = ((width - 2) / 2) + 1;
    maze_height = ((height - 2) / 2) + 1;

    std::cout << width << ", " << height << '\n';

    maze = std::unique_ptr<Cell[]>(new Cell[maze_width * maze_height]);
  }

  virtual void init() = 0;
  virtual void reset() = 0;
  virtual bool iterate() = 0;

 protected:
  int maze_width;
  int maze_height;
  std::unique_ptr<Cell[]> maze;

  static constexpr uint8_t wall_color[3] = {123, 37, 5};
  static constexpr uint8_t path_color[3] = {196, 119, 89};

  inline Cell* get_cell(int x, int y) {
    return &maze.get()[y * maze_width + x];
  }

 private:
};

#endif