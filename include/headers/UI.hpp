#ifndef UI_HPP
#define UI_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include "Button.hpp"
#include "Text.hpp"
#include "GameObject.hpp"
#include <vector>
#include <string>
using namespace std;

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI();
    void addButton(Button* button);
    void addText(Text* text);
    void addGameObject(GameObject* gameObject);
    void render();
    void removeText(Text* textToRemove);
    

private:
    SDL_Renderer* renderer;
    vector<Button*> buttons;
    vector<Text*> texts;
    vector<GameObject*> gameObjects;
};

#endif // UI_HPP