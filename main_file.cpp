#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>

using std::cout;

// configure your project with vscode
// tasks.json (compiler build settings)
// launch.json (debugger settings)q
// c_cpp_properties.json (compiler path and IntelliSense settings)


using std::printf;
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
int SCREEN_WIDTH=500;
int SCREEN_HEIGHT=500;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout<< "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            cout <<  "Window could not be created! SDL Error: %s\n" << SDL_GetError();
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
        }
    }
    return success;
}

// SDL_Surface* loadSurface( std::string path )
// {
//     //The final optimized image
//     SDL_Surface* optimizedSurface = NULL;

//     //Load image at specified path
//     SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//     if( loadedSurface == NULL )
//     {
//         cout<<  "Unable to load image %s! SDL_image Error: %s\n";
//     }
//     else
//     {
//         //Convert surface to screen format
//         optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
//         if( optimizedSurface == NULL )
//         {
//             cout << "Unable to optimize image %s! SDL Error: %s\n";
//         }

//         //Get rid of old loaded surface
//         SDL_FreeSurface( loadedSurface );
//     }

//     return optimizedSurface;
// }

// // bool loadMedia()
// // {
//     //Loading success flag
//     bool success = true;

//     //Load splash image
//     gHelloWorld = loadSurface( "images/grass.png" );
//     if( gHelloWorld == NULL )
//     {
//         cout<< "Unable to load image %s! SDL Error: %s\n"<<"images/grass.png";
//         success = false;
//     }

//     return success;
// }

// void close()
// {
//     //Deallocate surface
//     SDL_FreeSurface( gHelloWorld );
//     gHelloWorld = NULL;

//     //Destroy window
//     SDL_DestroyWindow( gWindow );
//     gWindow = NULL;

//     //Quit SDL subsystems
//     SDL_Quit();
// }

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    init();
    
    // Load media
    std::cout << "initialized";
    loadMedia();
   
    bool is_running = true;
    SDL_Event event;
    while (is_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
        SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        SDL_UpdateWindowSurface( gWindow );
        }
        SDL_Delay(1000);
    }
    close();

    return 0;
}


