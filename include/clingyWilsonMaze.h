#ifndef CLINGYWILSONMAZE_H
#define CLINGYWILSONMAZE_H

#include "wilsonMaze.h"

class ClingyWilsonMaze : public WilsonMaze {
 public:
  ClingyWilsonMaze(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height, float scale = 1.0) : WilsonMaze(renderer, window_width, window_height, width, height, scale) {}

 private:
  bool do_walking() override;
	std::optional<wilson_cell*> find_visited_cell(int x, int y);
};

#endif