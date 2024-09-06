#ifndef MENU_HPP
#define MENU_HPP

#include "Button.hpp"
#include "UI.hpp"
#include <SDL.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void handleEvent(SDL_Event* event);
    void update();
    void drawMainMenu();

private:
    UI ui;
    int currentSelection;
    Button* startButton;
    Button* quitButton;
    Button* leftArrowButton;
    Button* rightArrowButton;
    SDL_Renderer* renderer;

    void startButtonClicked();
    void quitButtonClicked();
    void leftArrowClicked();
    void rightArrowClicked();
    TTF_Font* font;

};



#endif // MENU_HPP