#ifndef UI_HPP
#define UI_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include "Button.hpp"
#include "Text.hpp"
#include <vector>
#include <string>
using namespace std;

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI();
    void addButton(Button* button);
    void addText(Text* text);
    void render();

private:
    SDL_Renderer* renderer;
    vector<Button*> buttons;
    vector<Text*> texts;
};

#endif // UI_HPP