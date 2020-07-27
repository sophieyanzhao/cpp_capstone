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
  //variables 
  int game_duration{30};
  int game_start{(int)SDL_GetTicks()};
  int time_remaining;
  std::size_t kScreenWidth, kScreenHeight;
  int intWidth, intHeight;
  std::shared_ptr<MutexVariable<bool>> running=std::make_shared<MutexVariable<bool>>(true);
  std::shared_ptr<MutexVariable<bool>> exited=std::make_shared<MutexVariable<bool>>(true);
  std::shared_ptr<bool> reset = std::make_shared<bool>(false);
  
  Game(std::size_t kScreenWidth, std::size_t kScreenHeight);
  void Init(); // restart the game 
  void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
  bool LegalPos(int x, int y);
  ~Game();

 private:
  int concurrency{5}; // number of moles appearing at the same time
  std::vector<std::shared_ptr<Mole>> _moles;
  std::shared_ptr<Score> score = std::make_shared<Score>();
};

#endif