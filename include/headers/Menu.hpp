// #ifndef MENU_HPP
// #define MENU_HPP

// #include <../sdl/SDL.h>
// #include "Button.hpp"
// #include "Assets.hpp"
// #include "UI.hpp"
// #include "Grid.hpp"
// #include <vector>
// #include <iostream>
// using namespace std;

// class Menu {                                                        // Menu class used for creating the main menu, game menu and game state screen
// public:
//     Menu(SDL_Renderer* renderer);                                   // Constructor  
//     ~Menu();                                                        // Destructor       

//     void handleEvent(SDL_Event* event);                             // Public methods
//     void update();
//     void startButtonClicked();
//     void quitButtonClicked();
//     void leftArrowClicked();
//     void rightArrowClicked();
//     void drawMainMenu();
//     void drawGame();
//     void handleInput(SDL_Keycode key);

// private:
//     UI ui;                                                          // Member variables                
//     int currentSelection;
//     Button* startButton, *quitButton, *leftArrowButton, *rightArrowButton, *restartButton, *undoButton, *backButton;
//     SDL_Renderer* renderer;
//     GameObject* gridImage, *background, *scoreBoard, *gameOver, *gameWin;
//     Grid* gridObject;
//     SDL_Event* event;
//     Text* scoreText, *gameOverText, *gameWinText, *continueText, *gridText; 
//     TTF_Font* font, *font1, *font2, *font3;
//     vector<string> gridOptions;
//     bool gameOverHandled = false;
//     bool gameWinHandled = false;
//     bool gameAlreadyWon = false;
//     bool isMainMenuActive;
//     bool isGameMenuActive;

//     string getGameGridTexture(int selection);                       // Private methods
// };

// #endif // MENU_HPP