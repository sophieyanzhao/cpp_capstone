#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"


class Renderer {
 public:
  //constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  //destructor 
  ~Renderer();

  void RenderWindow();
  void UpdateWindowTitle(int score, int fps);
  SDL_Surface* LoadSurface(std::string path);


 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface* back_surface;
  SDL_Surface* front_surface;



  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif