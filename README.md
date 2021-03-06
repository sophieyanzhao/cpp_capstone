## Whac A Mole Video Game
This is Sophie's capstone project for Udacity's C++ Nanodegree. Whac a Mole was a very popular arcade game when I was young and I still remember playing on those coin-op machines on my way home from school. Now is a good chance to try bringing it into a video form with my c++ learning. Graphics are scraped from a free game platform called 4399.com.
### Game Rules

![instruction](/images/cpp_capstone_instruction.png)
* User can hit each mole at the top area to score 1 point (see the white outline in the graph above as an example). The scoring area is smaller when the mole is half hidden in the hole than when the mole is fully straight up. 
* After being hit the mole will disappear and a new one will come up after some wait time.
* User has a maximum of 30 seconds. After one round ends, user can press `r` key to restart the game. The operation will not be effective if the previous game hasn't timed out yet.
* In order to create asynchronous behaviors, each mole may hide 0-3 seconds before starting to move.
* User may click the x on the top left corner to exit, or simply press the `esc` key.

## Structure
### File Structure
```
cpp_capstone
│   README.md  
│   rubrics.md
└─── src 
|   |   main.cpp
|   |   game.h
|   |   game.cpp
│   │   controller.cpp 
│   │   controller.h 
│   │   graphics.cpp
|   |   graphics.h
|   |   renderer.h
|   |   renderer.cpp
|   |   mutexvariable.cpp 
|   |   mutexvariable.h
└───images 
|   | ...
|
└───build 
    |   file021.txt
```

### Class Structure 
![class structure](/images/cpp_capstone_flowchart.png)


  
## Installation Instruction

### CMAKE

The udacity workspace does not have SDL_image installed, so first run :
`apt-get install libsdl2-image-dev`

Next, make a folder named build (or anything). Type in the following commands in order to start the program:

`cd build`
`cmake ..`
`./WhacAMole`

### VScode in MAC

If you use vscode on Mac and you have installed sdl and related extentions inside your framework folder, you can simply go to main.cpp.
Then from the top menu bar of vscode, click Terminal-> Run Build Task.
You can then run the file named "WhacAMole" in your src folder.

* If you installed your SDL library and extentions elsewhere, you need to modify configs in .vscode
* In addition, the current paths are customized to Udacity's ubuntu server. If you use vscode, please switch all include statement such as `include <SDL2/name.h> to simply <name.h>

