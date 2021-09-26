#ifndef DEPTHFIRSTMAZE_H
#define DEPTHFIRSTMAZE_H

#include "maze.h"

struct depth_first_cell {
  int x;
  int y;
  bool visited;
};

class DepthFirstMaze : public Maze<depth_first_cell> {
 public:
  DepthFirstMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze<depth_first_cell>(renderer, window_width, window_height, width, height, scale) {}

  void init() override;
	void reset() override;
  bool iterate() override;

 private:
  std::stack<depth_first_cell*> cell_stack;

  std::vector<depth_first_cell*> get_unvisited_neighbors(depth_first_cell* c);
  void connect(depth_first_cell* c1, depth_first_cell* c2);
  depth_first_cell* get_random_neighbor(const std::vector<depth_first_cell*>& neighbors);
  depth_first_cell* push_cell(int x, int y);
  inline void push_back_cell(std::vector<depth_first_cell*>& cells, int x, int y);
  inline void push_cell(depth_first_cell* cell);
  inline void set_x(int x, int y, int newx);
  inline void set_y(int x, int y, int newy);
  inline void set_visited(int x, int y, bool v = true);
  inline bool get_is_visited(int x, int y);
};

#endif