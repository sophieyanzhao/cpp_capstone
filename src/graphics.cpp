#include "graphics.h"
#include <SDL_image.h>
#include "SDL_surface.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using std::cout;

Graphics::Graphics(){
    grass = LoadSurface("../images/smaller_grass.png");
    for (int i = 0; i < 6; i++){
            SDL_Surface* loaded_surface = LoadSurface(file_paths[i]);
            pictures.push_back(loaded_surface);
        }
    }

Graphics::~Graphics(){
    for (uint i=0; i<pictures.size(); i++){
        SDL_FreeSurface( pictures[i] );
        pictures[i]=nullptr;
    }
}

SDL_Surface* Graphics::LoadSurface(std::string path){
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL)
    {
        SDL_Log("Unable to load image! SDL_image Error\n");
        
    }
    // else
    // {   
    //     //Convert surface to screen format
    //     optimizedSurface = SDL_ConvertSurface(loadedSurface,format,0 );
    //     if( optimizedSurface == NULL ){
    //         SDL_Log("Unable to optimize image! SDL Error:\n");
    //         return loadedSurface;
    //     }else{

    //     //Get rid of old loaded surface
    //     SDL_FreeSurface(loadedSurface);
    //     return optimizedSurface;
    return loadedSurface;
    }

Mole::Mole(int x, int y, std::shared_ptr<MutexVariable<bool>> game_state){
      stretchRect.x = x;
      stretchRect.y = y;
      stretchRect.w = 250 ;
      stretchRect.h = round(250*ratio);
      mole_start = SDL_GetTicks();
      running=game_state;
}


Mole::~Mole(){ 
};

// bool Mole::GetGameState(){
//     std::unique_lock<std::mutex> lck(_mutex);
//     bool state=*running;
//     lck.unlock();
//     return state;
// }

void Mole::Update(){
    Uint32 mole_start = SDL_GetTicks();
    std::stringstream ss;
    auto myid = std::this_thread::get_id();
    ss << ""<< myid;
    string mystring = ss.str();
    SDL_Log("mole");
    SDL_Log(mystring.c_str());
    while (running->get()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto myid = std::this_thread::get_id();
     Uint32 mole_cycle_start = mole_start;
     Uint32  mole_now = SDL_GetTicks();
    if ((mole_now-mole_cycle_start)>update_duration){
        stage = MoleStage((stage+1)%MoleStage::end);
        mole_cycle_start = SDL_GetTicks();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    }
   
    SDL_Log( "exitting out of Update loop");
    SDL_Log(mystring.c_str());
};

