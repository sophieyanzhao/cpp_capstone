#include "game.h"
#include <iostream>
#include "SDL.h"
#include "controller.h"
using std::cout;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()){
      for (int mole_id=0; mole_id<_numer_of_moles;mole_id++){
       _moles.push_back(std::make_shared<Mole>(100*(mole_id+1), 100*(mole_id+1)));
       }
      for (std::shared_ptr<Mole> mole:_moles){
         threads.emplace_back(std::thread(&Mole::Update, mole));
       }
      //random_w(0, static_cast<int>(grid_width)),
      //random_h(0, static_cast<int>(grid_height)) {
};
Game::~Game(){
   std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  // initialize moles
  while (running) {
    frame_start = SDL_GetTicks();
    controller.HandleInput(running);

    // Input, Update, Render - the main game loop.
    Update();
    renderer.RenderWindow(_moles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, _moles);
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
}


void Game::Update() {
    // put updating logics here
}

int Game::GetScore() const { return score; }