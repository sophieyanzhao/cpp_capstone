#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
using std::cout;

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Whac A Mole", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);
  front_surface = SDL_GetWindowSurface(sdl_window);
  graphics=std::make_shared<Graphics>();

  if (nullptr == sdl_window || front_surface==nullptr) {
    std::cerr << "Window or surface could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  // Create renderer
  //(sdl_window, -1, SDL_RENDERER_ACCELERATED);
//   if (nullptr == sdl_renderer) {
//     std::cerr << "Renderer could not be created.\n";
//     std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
//   }
}

Renderer::~Renderer() {
    SDL_FreeSurface( front_surface );
    front_surface = nullptr;
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::RenderWindow(std::vector<std::shared_ptr<Mole>> moles) {
    SDL_BlitSurface(graphics->grass, NULL, front_surface, NULL );
    DrawMoles(moles);
    SDL_UpdateWindowSurface(sdl_window);
}

void Renderer::DrawMoles(std::vector<std::shared_ptr<Mole>> moles){
   for (auto mole: moles){
     SDL_BlitScaled(graphics->pictures[mole->stage], NULL, front_surface, &(mole->stretchRect));
   }
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Whac a mole: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

