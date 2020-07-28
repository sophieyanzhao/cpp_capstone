#include "game.h"
#include <iostream>
#include "SDL.h"
#include "controller.h"
#include "graphics.h"
#include <sstream>  
#include <future>
#include <cstdlib>
#include <cmath>
using std::pow;

Game::Game(std::size_t kScreenWidth, std::size_t kScreenHeight):time_remaining(game_duration){
      kScreenWidth = kScreenWidth;
      kScreenHeight = kScreenHeight;
      intWidth = (int) kScreenWidth;
      intHeight = (int) kScreenHeight;
      Init();

};

bool Game::LegalPos(int x, int y){
  if (x<1 || y<1){return false;}
  for (auto mole:_moles){if (pow(x-mole->stretchRect.x,2) +pow(y-mole->stretchRect.y,2)< pow(200,2)){return false;} }
  return true;
}

void Game::Init(){
   running->set(true);
   time_remaining=game_duration;

   // generate random position until we get a legal position
   std::random_device dev;
   std::mt19937 engine(dev());
   std::uniform_int_distribution<int> random_w(0, (intWidth-230));
   std::uniform_int_distribution<int> random_h(0, (intHeight-180)); 
   score->set(0);
   for (int mole_id=0; mole_id<concurrency;mole_id++){
       int x{0}, y{0};
       while (!LegalPos(x,y)){
       x=random_w(engine);
       y=random_h(engine);
       }
       _moles.push_back(std::make_shared<Mole>(x, y, running));
  }
};

Game::~Game(){
   SDL_Log("game destructor");
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 frame_start, frame_end, frame_duration;
  int frame_count = 0;
  // turn all mole on for movements
  for (std::shared_ptr<Mole> mole:_moles){
        mole->Simulate(score);
       
  }
  // the following commented codes are for concurrency debugging
  // auto myid = std::this_thread::get_id();
  // std::stringstream ss;
  // ss << myid;
  // string mystring = ss.str();
  // SDL_Log("main task id %s", mystring.c_str());
  while (running->get()||exited->get()) {
    if (*reset){
       game_start= (int)SDL_GetTicks();
       _moles.clear();
       frame_count=0;
       Init();
       for (std::shared_ptr<Mole> mole:_moles){
       mole->Simulate(score);}
       *reset=false;
    }
    frame_start = SDL_GetTicks();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    controller.HandleInput(running,exited,_moles,score,reset);
    // After every 1/10 second, update the window title.
    if (frame_count >= 100){
       if (running->get()){
          time_remaining=game_duration-((int)SDL_GetTicks()-game_start)/1000;
          if (time_remaining<0 && running->get()){
            time_remaining=0;
            running->set(false);
          }else if(_moles.size()<concurrency){
            std::uniform_int_distribution<int> random_w(0, (intWidth-230));
            std::uniform_int_distribution<int> random_h(0, (intHeight-180)); 
            for (int i=0; i<concurrency-_moles.size(); i++){
              std::random_device dev;
              std::mt19937 engine(dev());
              int x{0},y{0};
              while (!LegalPos(x,y)){
              x=random_w(engine);
              y=random_h(engine);
              }
              std::shared_ptr<Mole> mole = std::make_shared<Mole>(x, y, running);
              _moles.push_back(mole);
              mole->Simulate(score);
          }}
          }
      if (!running->get() && (_moles.size()>0)){
        _moles.clear();
      }
      renderer.RenderWindow(_moles);
      renderer.UpdateWindowTitle(score, time_remaining);
      frame_count = 0;
    }

    // delay the loop if it is running faster than a preset threshold 
    frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    frame_count+=target_frame_duration;
  }
  SDL_Log("game loop has ended");
}
