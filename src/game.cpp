#include "game.h"
#include <iostream>
#include "SDL.h"
#include "controller.h"
#include "graphics.h"
#include <sstream>  
#include <future>
// #include "assert.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()){
      Init();
      kScreenWidth = grid_width;
      kScreenHeight = grid_height;
      //random_w(0, static_cast<int>(grid_width)),
      //random_h(0, static_cast<int>(grid_height)) {
};

void Game::Init(){
   running->set(true);
   time_remaining=game_duration;
   score->set(0);
   for (int mole_id=0; mole_id<concurrency;mole_id++){
        // initialize moles
       _moles.push_back(std::make_shared<Mole>(100*(mole_id+1), 100*(mole_id+1), running));
  }
};

Game::~Game(){
   SDL_Log("game destructor");
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 frame_start, frame_end, frame_duration;
  int frame_count = 0;
  SDL_Log("game started running");
  for (std::shared_ptr<Mole> mole:_moles){
        mole->Simulate(score);
       
  }

  auto myid = std::this_thread::get_id();
  std::stringstream ss;
  ss << myid;
  string mystring = ss.str();
  SDL_Log("main task");
  SDL_Log(mystring.c_str());
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
    // Input, Update, Render - the main game loop.
    // renderer.RenderWindow(_moles);
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    // After every 1/10 second, update the window title.
    if (frame_count >= 100){
       if (running->get()){
          time_remaining=game_duration-((int)SDL_GetTicks()-game_start)/1000;
          if (time_remaining<1 && running->get()){
            SDL_Log("time is done!");
            running->set(false);
          }
          }
      
      renderer.RenderWindow(_moles);
      renderer.UpdateWindowTitle(score, time_remaining);
      frame_count = 0;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    frame_count+=target_frame_duration;
  }
  SDL_Log("game loop has ended");

}


int Game::GetScore() const { return score->get(); }