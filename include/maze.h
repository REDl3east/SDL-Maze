#ifndef MAZE_H
#define MAZE_H

#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <stack>

#include "pixelWorld.h"

struct cell {
  int x;
  int y;
  bool visited;
};

class Maze : public PixelWorld {
 public:
  Maze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : PixelWorld(renderer, window_width, window_height, width, height, scale) {
    if (width % 2 == 0) throw std::runtime_error("invalid arguments");
    if (height % 2 == 0) throw std::runtime_error("invalid arguments");

    maze_width = ((width - 2) / 2) + 1;
    maze_height = ((height - 2) / 2) + 1;

    maze = std::unique_ptr<cell[]>(new cell[maze_width * maze_height]);

    for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
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

    // point((0*2)+1, (126*2)+1, border_color[0], border_color[1], border_color[2]);
  };

  // Choose the initial cell, mark it as visited and push it to the stack
  // While the stack is not empty
  //   Pop a cell from the stack and make it a current cell
  //   If the current cell has any neighbours which have not been visited
  //     Push the current cell to the stack
  //     Choose one of the unvisited neighbours
  //     Remove the wall between the current cell and the chosen cell
  //     Mark the chosen cell as visited and push it to the stack

  bool iterate() {
    if (cell_stack.empty()) return false;

    auto* cell = cell_stack.top();
    cell_stack.pop();

    point((cell->x * 2 + 1), (cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);

    auto neighbors = get_unvisited_neighbors(cell);
    if (!neighbors.empty()) {
      cell_stack.push(cell);
      auto* rand_cell = get_random_neighbor(neighbors);
      connect(cell, rand_cell);
      rand_cell->visited = true;
      cell_stack.push(rand_cell);
    }

    return true;
  }

  ~Maze() {}

  std::vector<cell*> get_unvisited_neighbors(cell* c) {
    std::vector<cell*> ret;

    if ((c->x - 1 >= 0)) {
      if (!maze.get()[(c->x - 1) * maze_height + c->y].visited) {
        ret.push_back(&maze.get()[(c->x - 1) * maze_height + c->y]);
      }
    }

    if ((c->y - 1 >= 0)) {
      if (!maze.get()[c->x * maze_height + (c->y - 1)].visited) {
        ret.push_back(&maze.get()[c->x * maze_height + (c->y - 1)]);
      }
    }

    if ((c->x + 1 < maze_height)) {
      if (!maze.get()[(c->x + 1) * maze_height + c->y].visited) {
        ret.push_back(&maze.get()[(c->x + 1) * maze_height + c->y]);
      }
    }

    if ((c->y + 1 < maze_width)) {
      if (!maze.get()[c->x * maze_height + (c->y + 1)].visited) {
        ret.push_back(&maze.get()[c->x * maze_height + (c->y + 1)]);
      }
    }

    return ret;
  }

 private:
  int current_x = 0;
  int current_y = 0;
  int maze_width;
  int maze_height;
  std::unique_ptr<cell[]> maze;
  std::stack<cell*> cell_stack;
  static constexpr uint8_t wall_color[3] = {123, 37, 5};
  static constexpr uint8_t path_color[3] = {196, 119, 89};

  int index = 0;

  void connect(cell* c1, cell* c2) {
    int x_diff = c1->x - c2->x;
    int y_diff = c1->y - c2->y;
    if (x_diff == 0 && y_diff > 0) {
      point((c1->x * 2 + 1), (c1->y * 2 + 1 - 1), path_color[0], path_color[1], path_color[2]);
    } else if (x_diff == 0 && y_diff < 0) {
      point((c1->x * 2 + 1), (c1->y * 2 + 1 + 1), path_color[0], path_color[1], path_color[2]);
    } else if (y_diff == 0 && x_diff > 0) {
      point((c1->x * 2 + 1 - 1), (c1->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    } else if (y_diff == 0 && x_diff < 0) {
      point((c1->x * 2 + 1 + 1), (c1->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
    }
  }

  cell* get_random_neighbor(const std::vector<cell*>& neighbors) {
    assert(neighbors.size() > 0);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, neighbors.size()-1);
    return neighbors[dist(rng)];
  }

  cell* push_cell(int x, int y) {
    auto* cell = &maze.get()[x * maze_height + y];
    cell_stack.push(cell);
    return cell;
  }

  void set_x(int x, int y, int newx) {
    maze.get()[x * maze_height + y].x = newx;
  }
  void set_y(int x, int y, int newy) {
    maze.get()[x * maze_height + y].y = newy;
  }
  void set_visited(int x, int y, bool v = true) {
    maze.get()[x * maze_height + y].visited = v;
  }
};

#endif