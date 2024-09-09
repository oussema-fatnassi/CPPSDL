#ifndef MENU_HPP
#define MENU_HPP

#include "Button.hpp"
#include "UI.hpp"
#include <../sdl/SDL.h>
#include <vector>
#include "Grid.hpp"
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
    void drawGame();
    void handleInput(SDL_Keycode key);

private:
    UI ui;
    int currentSelection;
    Button* startButton, *quitButton, *leftArrowButton, *rightArrowButton;
    Button* restartButton, *undoButton;
    SDL_Renderer* renderer;
    GameObject* gridImage, *background, *scoreBoard, *gameOver, *gameWin;
    Text* gridText;
    Grid* gridObject;
    SDL_Event* event;
    Text* scoreText, *gameOverText, *gameWinText, *continueText; 

    TTF_Font* font, *font1, *font2;

    vector<pair<string, string>> gridOptions;
    string getGameGridTexture(int selection);
};



#endif // MENU_HPP