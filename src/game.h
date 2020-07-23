#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::shared_ptr<bool> running=std::make_shared<bool>(true);
  ~Game();

 private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::vector<std::thread> threads;
  std::vector<std::shared_ptr<Mole>> _moles;
  int concurrency{3};
  int score{0};

  void PlaceFood();
  void Update();
};

#endif