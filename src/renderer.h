#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "mole.h"
#include <queue>

class Renderer {
 public:
  //constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  //destructor 
  ~Renderer();

  void RenderWindow(std::vector<std::shared_ptr<Mole>> moles);
  void UpdateWindowTitle(int score, int fps,std::vector<std::shared_ptr<Mole>> moles);
  void DrawMoles(std::vector<std::shared_ptr<Mole>> moles);


 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface* back_surface;
  SDL_Surface* front_surface;
  //std::vector<Mole> _moles;
  std::shared_ptr<Graphics> graphics = std::make_shared<Graphics>();
  int _numer_of_moles{2};
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif