#ifndef KRUSKALMAZE_H
#define KRUSKALMAZE_H

#include "maze.h"

struct kruskal_cell {
  int id;
  std::vector<int> cell_set;
};

struct kruskal_edge {
  int x;
  int y;
  bool direction;  //true = up/down
                   //false = left/right
};

class KruskalMaze : public Maze<kruskal_cell> {
 public:
  KruskalMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : Maze<kruskal_cell>(renderer, window_width, window_height, width, height, scale) {}
  void init() override;
  void reset() override;
  bool iterate() override;

  ~KruskalMaze() {
  }

 private:
  std::vector<kruskal_edge> edge_set;

  // bool is_distinct_set(int x1, int y1, int x2, int y2) {
  //   //no elements in common
  //   for (auto s1 : maze[x1 * maze_height + y1].cell_set) {
  //     for (auto s2 : maze[x2 * maze_height + y2].cell_set) {
  //       if (s1 == s2) return false;
  //     }
  //   }

  //   return true;
  // }

  // void connect(int x1, int y1, int x2, int y2) {
  //   auto& set1 = maze[x1 * maze_height + y1].cell_set;
  //   auto& set2 = maze[x2 * maze_height + y2].cell_set;

  //   set1.insert(set2.begin(), set2.end());
  //   set2.insert(set1.begin(), set1.end());
  // }
};

#endif