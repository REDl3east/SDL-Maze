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
  void init() override;
  void reset() override;
  bool iterate() override;

 private:
  inline bool is_walked(int x, int y);
  inline void set_visited(int x, int y, bool v);
  inline void push_back_cell(std::vector<wilson_cell*>& cells, int x, int y);
  inline bool is_visited(int x, int y);
  inline void set_walked(int x, int y, bool v);
  inline void set_x(int x, int y, int newx);
  inline void set_y(int x, int y, int newy);

 protected:
  int current_x;
  int current_y;
  bool walking = true;
  bool new_walk = true;
  std::vector<wilson_cell*> walked_cells;
  std::vector<wilson_cell*> unvisited_cells;
  static constexpr uint8_t walking_color[3] = {252, 186, 3};

  void connect(wilson_cell* c1, wilson_cell* c2);
  std::optional<wilson_cell*> find_visited_cell(int x, int y);
  bool set_new_start();
  wilson_cell* get_random_neighbor(const std::vector<wilson_cell*>& neighbors);
  std::vector<wilson_cell*> get_neighbors(int x, int y);
  std::vector<wilson_cell*> get_unvisited_neighbors(int x, int y);
  virtual bool do_walking();
  void draw_walking();
  bool has_no_neighbors(const std::vector<wilson_cell*>& neighbors);
  bool did_set_new_start();
  void set_cell_to_walk(wilson_cell* cell);
};

#endif