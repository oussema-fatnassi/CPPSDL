#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Assets.hpp"
#include "UI.hpp"
#include "Grid.hpp"
#include <vector>
#include <iostream>
#include "ResourceManager.hpp"
using namespace std;

class Menu {                                                        // Menu class used for creating the main menu, game menu, and game state screen
public:
    Menu(sf::RenderWindow& window);                                 // Constructor  
    ~Menu();                                                        // Destructor       

    void handleEvent(sf::Event& event);                             // Public methods
    void update();
    void startButtonClicked();
    void quitButtonClicked();
    void leftArrowClicked();
    void rightArrowClicked();
    void drawMainMenu();
    void drawGame();
    void handleInput(sf::Keyboard::Key key);

private:
    UI ui;                                                          // Member variables                
    int currentSelection;
    Button* startButton, *quitButton, *leftArrowButton, *rightArrowButton, *restartButton, *undoButton, *backButton;
    GameObject* gridImage, *background, *scoreBoard, *gameOver, *gameWin;
    Text* scoreText, *gameOverText, *gameWinText, *continueText, *gridText, *selectGridText, *quitText, *startText, *title;
    Grid* gridObject;
    sf::Event* event;
    sf::Font* font;
    sf::RenderWindow* window;
    vector<string> gridOptions;
    bool gameOverHandled = false;
    bool gameWinHandled = false;
    bool gameAlreadyWon = false;
    bool isMainMenuActive;
    bool isGameMenuActive;

    string getGameGridTexture(int selection);                 // Private methods
};

#endif // MENU_HPP
