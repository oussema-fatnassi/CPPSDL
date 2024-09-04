#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SDL.h>

class InputHandler {
public:
    enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };
    
    Direction getDirection();

private:
    Direction mapSDLKeyToDirection(SDL_Keycode key);
};

#endif  // INPUTHANDLER_HPP
