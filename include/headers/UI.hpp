#ifndef UI_HPP
#define UI_HPP

#include <SDL.h>
#include "Button.hpp"
#include <vector>
using namespace std;

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI();
    void addButton(Button* button);
    void render();

private:
    SDL_Renderer* renderer;
    vector<Button> buttons;
};

#endif // UI_HPP