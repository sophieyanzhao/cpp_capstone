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
      for (int mole_id=0; mole_id<concurrency;mole_id++){
        // initialize moles
       _moles.push_back(std::make_shared<Mole>(100*(mole_id+1), 100*(mole_id+1), running));
       }
      //random_w(0, static_cast<int>(grid_width)),
      //random_h(0, static_cast<int>(grid_height)) {
};

Game::~Game(){
   SDL_Log("game destructor");
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
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
  while (running->get()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    frame_start = SDL_GetTicks();
    // assert !_moles.empty();
    controller.HandleInput(running,_moles,score);
  
    // Input, Update, Render - the main game loop.
    renderer.RenderWindow(_moles);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  SDL_Log("game loop has ended");

}


int Game::GetScore() const { return score->get(); }