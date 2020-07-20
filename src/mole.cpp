#include "mole.h"
#include <SDL_image.h>
#include "SDL_surface.h"
#include <iostream>
#include <cmath>
#include <string>
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
        cout<<  "Unable to load image %s! SDL_image Error: %s\n";
    }
    else
    {
        //Convert surface to screen format
        //optimizedSurface = SDL_ConvertSurface( loadedSurface,front_surface->format,0 );
        // if( optimizedSurface == NULL )
        // {
        //     cout << "Unable to optimize image %s! SDL Error: %s\n";
        // }

        //Get rid of old loaded surface
        //SDL_FreeSurface(loadedSurface);
    }

    //return optimizedSurface;
    return loadedSurface;
}

Mole::Mole(int x, int y){
      stretchRect.x = x;
      stretchRect.y = y;
      stretchRect.w = 250 ;
      stretchRect.h = round(250*ratio);
      mole_start = SDL_GetTicks();
      //t=std::thread(&Mole::Update, this)

    //   threads.emplace_back(&Mole::Update,this);


}


Mole::~Mole(){ 
    // std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
    //     t.join();
    // });
};

void Mole::Update(){
    Uint32 mole_now = SDL_GetTicks();
    while (SDL_GetTicks()-mole_now<2000){
   
    if ((mole_now-mole_start)>update_duration){
        stage = MoleStage((stage+1)%MoleStage::end);
        mole_start = SDL_GetTicks();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    }
};

