#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Assets.hpp"
#include "UI.hpp"
#include "Grid.hpp"
#include <vector>
#include <iostream>

class Menu {                                                        // Menu class used for creating the main menu, game menu, and game state screen
public:
    Menu(sf::RenderWindow& window);                                  // Constructor  
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
    Button* startButton;
    Button* quitButton;
    Button* leftArrowButton;
    Button* rightArrowButton;
    Button* restartButton;
    Button* undoButton;
    Button* backButton;
    sf::RenderWindow* window;
    GameObject* gridImage;
    GameObject* background;
    GameObject* scoreBoard;
    GameObject* gameOver;
    GameObject* gameWin;
    Grid* gridObject;
    sf::Event* event;
    Text* scoreText;
    Text* gameOverText;
    Text* gameWinText;
    Text* continueText;
    Text* gridText;
    Text* selectGridText;
    Text* quitText;
    Text* startText;
    Text* title;
    sf::Font* font;
    sf::Font* font1;
    sf::Font* font2;
    sf::Font* font3;
    std::vector<std::string> gridOptions;
    bool gameOverHandled = false;
    bool gameWinHandled = false;
    bool gameAlreadyWon = false;
    bool isMainMenuActive;
    bool isGameMenuActive;

    std::string getGameGridTexture(int selection);                 // Private methods
};

#endif // MENU_HPP
