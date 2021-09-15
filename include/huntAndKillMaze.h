#ifndef HUNTANDKILLMAZE_H
#define HUNTANDKILLMAZE_H

#include <utility>

#include "maze.h"

struct hunt_and_kill_cell {
  int x;
  int y;
  bool visited;
};

class HuntAndKillMaze : public Maze<hunt_and_kill_cell> {
 public:
  HuntAndKillMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze(renderer, window_width, window_height, width, height, scale) {}
  void init() override;
  void reset() override;
  bool iterate() override;

 private:

  std::vector<hunt_and_kill_cell*> get_visited_neighbors(hunt_and_kill_cell* c);
	std::vector<hunt_and_kill_cell*> get_unvisited_neighbors(hunt_and_kill_cell* c);
  void connect(hunt_and_kill_cell* c1, hunt_and_kill_cell* c2);
  hunt_and_kill_cell* get_random_neighbor(const std::vector<hunt_and_kill_cell*>& neighbors);
  inline void push_back_cell(std::vector<hunt_and_kill_cell*>& cells, int x, int y);
  inline void set_x(int x, int y, int newx);
  inline void set_y(int x, int y, int newy);
  inline void set_visited(int x, int y, bool v = true);
  inline bool get_is_visited(int x, int y);

  std::optional<hunt_and_kill_cell*> hunt();
	bool hunting = false;
	hunt_and_kill_cell* current_cell;
};

#endif