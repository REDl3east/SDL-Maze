#ifndef WILSONMAZE_H
#define WILSONMAZE_H

#include "maze.h"

struct wilson_cell {
  bool visited;
  bool walked = false;
  int x;
  int y;
};

class WilsonMaze : public Maze<wilson_cell> {
 public:
  WilsonMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze(renderer, window_width, window_height, width, height, scale) {}
  void init() override {
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

    int tmp_x = maze_width / 2;
    int tmp_y = maze_height / 2;
    set_visited(tmp_x, tmp_y, true);
    point((tmp_x * 2 + 1), (tmp_y * 2 + 1), path_color[0], path_color[1], path_color[2]);
  };
  void reset() override{

  };
  bool iterate() override {
    if (walking) {
      if (new_walk) {
        new_walk = false;
        //choose random starting location
        if (!set_new_starting()) return false;
      }

      point((current_x * 2 + 1), (current_y * 2 + 1), walking_color[0], walking_color[1], walking_color[2]);

      //first see if any cells are visited
      auto visited_cell_opt = find_visited_cell(current_x, current_y);
      if (visited_cell_opt) {
        connect(visited_cell_opt.value(), walked_cells.back());
        walking = false;
        return true;
      }

      //find unvisted neighbors
      auto unvisited_cells = get_unvisited_neighbors(current_x, current_y);
      if (unvisited_cells.size() == 0) {
        new_walk = true;

        //clear walked cells
        while (!walked_cells.empty()) {
          auto* cell = walked_cells.back();
          walked_cells.pop_back();
          set_walked(cell->x, cell->y, false);
          point((cell->x * 2 + 1), (cell->y * 2 + 1), wall_color[0], wall_color[1], wall_color[2]);
        }

        return true;
      }
      auto* random_cell = get_random_neighbor(unvisited_cells);
      current_x = random_cell->x;
      current_y = random_cell->y;
      set_walked(current_x, current_y, true);
      walked_cells.push_back(random_cell);
    } else {
      wilson_cell* last_cell = nullptr;

      while (!walked_cells.empty()) {
        auto* cell = walked_cells.back();
        walked_cells.pop_back();
        set_walked(cell->x, cell->y, false);
        set_visited(cell->x, cell->y, true);
        point((cell->x * 2 + 1), (cell->y * 2 + 1), path_color[0], path_color[1], path_color[2]);
        if (last_cell != nullptr) connect(cell, last_cell);

        last_cell = cell;
      }

      walking = true;
      new_walk = true;
      return true;
    }

    return true;
  };

 private:
  int current_x;
  int current_y;
  bool walking = true;
  bool new_walk = true;

  std::vector<wilson_cell*> walked_cells;
  std::vector<wilson_cell*> unvisited_cells;
  static constexpr uint8_t walking_color[3] = {252, 186, 3};

  void connect(wilson_cell* c1, wilson_cell* c2) {
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

  std::optional<wilson_cell*> find_visited_cell(int x, int y) {
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

  bool set_new_starting() {
    if (unvisited_cells.empty()) return false;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, unvisited_cells.size() - 1);
    auto* cell = unvisited_cells[dist(rng)];
    current_x = cell->x;
    current_y = cell->y;
    set_walked(current_x, current_y, true);
    walked_cells.push_back(cell);

    return true;
  }
  wilson_cell* get_random_neighbor(const std::vector<wilson_cell*>& neighbors) {
    assert(neighbors.size() > 0);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, neighbors.size() - 1);
    return neighbors[dist(rng)];
  }
  std::vector<wilson_cell*> get_unvisited_neighbors(int x, int y) {
    std::vector<wilson_cell*> ret;

    if ((x - 1 >= 0)) {
      if (!is_visited((x - 1), y) && !is_walked(x - 1, y)) {
        push_back_cell(ret, x - 1, y);
      }
    }
    if ((y - 1 >= 0)) {
      if (!is_visited(x, (y - 1)) && !is_walked(x, y - 1)) {
        push_back_cell(ret, x, y - 1);
      }
    }
    if ((x + 1 < maze_height)) {
      if (!is_visited((x + 1), y) && !is_walked(x + 1, y)) {
        push_back_cell(ret, x + 1, y);
      }
    }
    if ((y + 1 < maze_width)) {
      if (!is_visited(x, (y + 1)) && !is_walked(x, y + 1)) {
        push_back_cell(ret, x, y + 1);
      }
    }

    return ret;
  }
  inline void push_back_cell(std::vector<wilson_cell*>& cells, int x, int y) {
    cells.push_back(&maze.get()[x * maze_height + y]);
  }
  inline bool is_visited(int x, int y) {
    return maze.get()[x * maze_height + y].visited;
  }
  inline bool is_walked(int x, int y) {
    return maze.get()[x * maze_height + y].walked;
  }
  inline void set_visited(int x, int y, bool v) {
    if (v) {
      auto* cell = get_cell(x, y);
      unvisited_cells.erase(std::remove_if(unvisited_cells.begin(), unvisited_cells.end(), [&cell](auto* x) { return x == cell; }));
    } else {
      unvisited_cells.push_back(get_cell(x, y));
    }
    maze.get()[x * maze_height + y].visited = v;
  }
  inline void set_walked(int x, int y, bool v) {
    maze.get()[x * maze_height + y].walked = v;
  }
  inline void set_x(int x, int y, int newx) {
    maze.get()[x * maze_height + y].x = newx;
  }

  inline void set_y(int x, int y, int newy) {
    maze.get()[x * maze_height + y].y = newy;
  }
};

#endif