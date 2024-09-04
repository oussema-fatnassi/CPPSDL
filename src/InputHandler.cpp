#include "InputHandler.hpp"
#include <iostream>
using namespace std;

InputHandler::Direction InputHandler::getDirection() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            return mapSDLKeyToDirection(event.key.keysym.sym);
        } else if (event.type == SDL_QUIT) {
            return Direction::NONE;
        }
    }
    return Direction::NONE;
}

InputHandler::Direction InputHandler::mapSDLKeyToDirection(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            cout << "UP" << endl;
            return Direction::UP;
        case SDLK_DOWN:
            cout << "DOWN" << endl;
            return Direction::DOWN;
        case SDLK_LEFT:
            cout << "LEFT" << endl;
            return Direction::LEFT;
        case SDLK_RIGHT:
            cout << "RIGHT" << endl;
            return Direction::RIGHT;
        default:
            cout << "NONE" << endl;
            return Direction::NONE;
    }
}
