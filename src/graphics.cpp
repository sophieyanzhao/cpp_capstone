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
    for (int i = 0; i <file_paths.size() ; i++){
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
    //emplace back calls constructor, push_back calls copy constructor
    moving_task.join();
    check_alive_task.join();
    SDL_Log("mole destructor succcessfull joined all threads");
};


void Mole::Simulate(std::shared_ptr<Score> score){
    moving_task = std::thread(&Mole::Update, this);
    check_alive_task=std::thread(&Mole::CheckAlive, this, score, running);
}



void Mole::Update(){
    // add some asynchronous behaviors to mole 
    // Uint32 start = SDL_GetTicks();
    // std::random_device dev;
    // std::mt19937 engine(dev());
    // std::uniform_int_distribution<Uint32> waitTimeGen(0, 3000);
    // Uint32 waitTime = waitTimeGen(engine);
    // while ((SDL_GetTicks()-start)<waitTime){
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }
    Uint32 mole_start = SDL_GetTicks();
    std::stringstream ss;
    auto myid = std::this_thread::get_id();
    ss << ""<< myid;
    string mystring = ss.str();
    SDL_Log("mole");
    SDL_Log(mystring.c_str());
    while (running->get()&&alive->get()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto myid = std::this_thread::get_id();
        if ((SDL_GetTicks()-mole_start)>update_duration){
        idx=(idx+1)%8;
        stage = transition[idx];
        //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        mole_start = SDL_GetTicks();
    }
    }
    // send signal to end the CheckAlive Task
    hit_signals->send(Position(-1, -1));
    SDL_Log("exitting out of Update loop");
    SDL_Log(mystring.c_str());
};

// bool Mole::CheckAlive(std::shared_ptr<MutexVariable<bool>> alive){

// }

bool Mole::Hit(int &x,int &y){
    bool cond1 = (x>stretchRect.x + 70);
    bool cond2 = (x<stretchRect.x + 150);
    bool cond3 = (y<stretchRect.y+70); // bottom is 85 but we can make it more difficult 
    bool cond4 = y-(2.0/39.0)*x > (stretchRect.y+60.0-(2.0/39.0)*(stretchRect.x+70.0))-offset[stage];
    bool cond5 = y+(2.0/39.0)*x > (stretchRect.y+62.0+(218.0+2.0*stretchRect.x)/39.0)-offset[stage];
    return (cond1 && cond2 && cond3 && cond4 && cond5);
}


void Mole::CheckAlive(std::shared_ptr<Score> score , std::shared_ptr<MutexVariable<bool>> running){
    while (running->get() && alive->get()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        Position p = hit_signals->receive();
        std::string hitMessage="the mole gets hitted: at"+std::to_string(p._x) + " , "+ std::to_string(p._y);
        SDL_Log(hitMessage.c_str());
        if (Hit(p._x, p._y)){
            score->AddOne();
            alive->set(false);
        }else if (p._x<0 && p._y <0){
            alive->set(false);
        }
    }
    SDL_Log("mole is dying now");
}