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

void Renderer::RenderWindow() {
    back_surface = LoadSurface("../images/smaller_grass.png");
    SDL_BlitSurface(back_surface, NULL, front_surface, NULL );
    SDL_UpdateWindowSurface(sdl_window);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Whac a mole: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


SDL_Surface* Renderer::LoadSurface( std::string path ){
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout<<  "Unable to load image %s! SDL_image Error: %s\n";
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, front_surface->format, 0 );
        if( optimizedSurface == NULL )
        {
            cout << "Unable to optimize image %s! SDL Error: %s\n";
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}