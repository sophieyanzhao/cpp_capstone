## Project Description
Describes the project you have built.
The README also indicates the file and class structure, along with the expected behavior or output of the program.

## Game Rules


## Installation Instruction




## Rubrics satisfied (make this a hyperlink)

1. The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
Explanation: The game load image files and scale them to display onto the screen

2. The project accepts user input and processes the input.
Explanation: The game takes user input to restart/exit/score.

3. The project uses Object Oriented Programming techniques.
Explanation: All game elements are wrapped into classes, such as controller, game, message_queue, moles etc.

4. Class constructors utilize member initialization lists.
TODO: change here; 

5. Templates generalize functions in the project.
Explanation: mutexvariable with thread-safe getter/setter uses template.

6. The project makes use of references in function declarations.
Explanation: most variables are shared pointers to ensure no excessive memory are taken to copy the objects.

7. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
Explanation: the mole object class manages two threads individually and handle them before being destructed.

8. The project uses multithreading.
Explanation: Each mole has two threads: 1 thread for updating mole stage, 1 thread for checking user mouse click position.

9. A condition variable is used in the project.
Explanation: message queue uses condition variable to wait for user mouse click location information sent from controller object.






Use Cmake/make 