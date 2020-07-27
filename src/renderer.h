#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "graphics.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  void RenderWindow(std::vector<std::shared_ptr<Mole>> &moles);
  void DrawMoles(std::vector<std::shared_ptr<Mole>> &moles);
  void UpdateWindowTitle(std::shared_ptr<Score> score, int fps);
  ~Renderer();

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface* front_surface;
  std::shared_ptr<Graphics> graphics;
  int _concurrency{1};
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif