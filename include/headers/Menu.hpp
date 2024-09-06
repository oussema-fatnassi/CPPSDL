#ifndef MENU_HPP
#define MENU_HPP

#include "Button.hpp"
#include "UI.hpp"
#include <../sdl/SDL.h>
#include <vector>
using namespace std;

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void handleEvent(SDL_Event* event);
    void update();
    void startButtonClicked();
    void quitButtonClicked();
    void leftArrowClicked();
    void rightArrowClicked();
    void drawMainMenu();

private:
    UI ui;
    int currentSelection;
    Button* startButton;
    Button* quitButton;
    Button* leftArrowButton;
    Button* rightArrowButton;
    SDL_Renderer* renderer;
    GameObject* gridImage;
    Text* gridText;

    TTF_Font* font;
    TTF_Font* font1;

    vector<pair<string, string>> gridOptions;

};



#endif // MENU_HPP