#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "mutexvariable.h"
#include <future>

class Game {
 public:
  Game(std::size_t kScreenWidth, std::size_t kScreenHeight);
  void Init(); // restart the game 
  void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int game_start{(int)SDL_GetTicks()};
  int time_remaining{60};
  std::size_t kScreenWidth;
  std::size_t kScreenHeight;
  int intWidth, intHeight;
  int game_duration{5};
  int GetSize() const;
  std::shared_ptr<MutexVariable<bool>> running=std::make_shared<MutexVariable<bool>>(true);
  std::shared_ptr<MutexVariable<bool>> exited=std::make_shared<MutexVariable<bool>>(true);
  std::shared_ptr<bool> reset = std::make_shared<bool>(false);
  bool LegalPos(int x, int y);
  ~Game();

 private:
  std::random_device dev;
  std::mt19937 engine;
  std::vector<std::shared_ptr<Mole>> _moles;
  int concurrency{4};
  std::shared_ptr<Score> score = std::make_shared<Score>();
};

#endif