/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <cstdlib>
#include <ctime>

#include "Window.h"

int main(int argc, char** argv) {
    if (argc && argv); //pour éviter un warning.....
    
    std::srand(std::time(NULL));
    
    Window* window = new Window(true);
    
    window->loop();
    
    delete window;
    
    return 0;
}
