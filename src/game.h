#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "mole.h"
#include <thread>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::vector<std::shared_ptr<Mole>> _moles;

 private:
  SDL_Point food;
  int _numer_of_moles{2};
  std::random_device dev;
  std::mt19937 engine;
  std::vector<std::thread> threads;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int score{0};

  void PlaceFood();
  void Update();
};

#endif