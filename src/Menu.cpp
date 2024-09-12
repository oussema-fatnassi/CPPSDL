#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window) :  window(&window), ui(window), currentSelection(1), restartButton(nullptr), undoButton(nullptr) {         // Constructor

    gridOptions = {                                                                         // Grid options for the main menu
        IMAGE_GRID_3X3,
        IMAGE_GRID_4X4,
        IMAGE_GRID_5X5,
        IMAGE_GRID_6X6,
        IMAGE_GRID_8X8
    };
    drawMainMenu();   
    isMainMenuActive = true;
    isGameMenuActive = false;
}

Menu::~Menu() {}

void Menu::drawMainMenu() {                                                         // Draw the main menu with the grid selection
    isMainMenuActive = true;
    isGameMenuActive = false;

    font = new sf::Font();
    font->loadFromFile(FONT_PATH);

    title = new Text(*window, "2048", *font, sf::Color(113, 112, 107), 225, 50, 1,60);
    startText = new Text(*window, "Start", *font, sf::Color::White, 225, 650, 1,60);
    quitText = new Text(*window, "Quit", *font, sf::Color::White, 235, 740, 1,60);

    gridImage = new GameObject(*window, gridOptions[currentSelection], 150, 200, 300, 300);

    startButton = new Button(*window, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 146, 650, 308, 80, [this] { startButtonClicked(); });
    quitButton = new Button(*window, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 146, 750, 308, 80, [this] { quitButtonClicked(); });
    leftArrowButton = new Button(*window, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 310, 34, 74, [this] { leftArrowClicked(); });
    rightArrowButton = new Button(*window, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 465, 310, 34, 74, [this] { rightArrowClicked(); });

    selectGridText = new Text(*window, "Select Grid Size", *font, sf::Color(113, 112, 107), 190, 560, 1,30);

    ui.addButton(startButton);                                                      // Add all the UI elements to the UI object to be rendered
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);
    ui.addText(title);
    ui.addText(startText);
    ui.addText(quitText);
    ui.addGameObject(gridImage);
    ui.addText(selectGridText);
    ui.render();
}

void Menu::drawGame() {                                                             // Draw the game menu with the grid and game elements
    isMainMenuActive = false;
    isGameMenuActive = true;
    ui.clear();

    gameOver = new GameObject(*window, GAME_OVER, 75, 300, 450, 450);
    gameWin = new GameObject(*window, GAME_WIN, 75, 300, 450, 450);

    gameOverText = new Text(*window, "GAME OVER!", *font, sf::Color(113, 112, 107), 135, 480, 1,60);
    gameWinText = new Text(*window, "YOU WON!", *font, sf::Color(113, 112, 107), 155, 450, 1,60);
    continueText = new Text(*window, "Move to continue", *font, sf::Color(113, 112, 107), 220, 530, 1,20);

    switch (currentSelection) {                                                     // Set the grid object based on the current selection
        case 0: gridObject = new Grid(3); break;
        case 1: gridObject = new Grid(4); break;
        case 2: gridObject = new Grid(5); break;
        case 3: gridObject = new Grid(6); break;
        case 4: gridObject = new Grid(8); break;
        default: gridObject = new Grid(4); break;
    }
    ui.setGrid(gridObject);

    restartButton = new Button(*window, RESTART_BUTTON_NORMAL, RESTART_BUTTON_HOVER, RESTART_BUTTON_PRESSED, 465, 200, 50, 50, [this] {
        gameAlreadyWon = false;
        gameWinHandled = false;
        gridObject->reset();
        ui.updateScoreText("0");
        ui.setGrid(gridObject);
        if (gameOverHandled) {
            ui.removeGameObject(gameOver);
            ui.removeText(gameOverText);
            gameOverHandled = false;
            std::cout << "Game restarted, game over UI elements removed." << std::endl;
        }
        ui.clear();
        drawGame();
    });

    undoButton = new Button(*window, UNDO_BUTTON_NORMAL, UNDO_BUTTON_HOVER, UNDO_BUTTON_PRESSED, 365, 200, 50, 50, [this] {
        gridObject->undo();
        ui.setGrid(gridObject);
        ui.renderGame();
        ui.updateScoreText(std::to_string(gridObject->getScore()));
    });

    backButton = new Button(*window, BACK_BUTTON_NORMAL, BACK_BUTTON_HOVER, BACK_BUTTON_PRESSED, 230, 770, 135, 80, [this] {
        if (gridObject) {
            delete gridObject;
        }
        ui.setGrid(gridObject);
        ui.render();

        ui.clear();
        isMainMenuActive = true;
        isGameMenuActive = false;
        drawMainMenu();
    });
    
    ui.addText(new Text(*window, "SCORE", *font, sf::Color(113, 112, 107), 405, 105, 1,20));
    ui.addText(new Text(*window, "0", *font, sf::Color(251, 248, 239), 385, 120, 2,40));
    ui.addText(new Text(*window, "2048", *font, sf::Color(113, 112, 107), 50, 100, 1,60));
    ui.addText(new Text(*window, "Back", *font, sf::Color::White, 265, 785, 1,30));
    ui.addGameObject(new GameObject(*window, SCORE, 350, 100, 180, 80));
    ui.addGameObject(new GameObject(*window, getGameGridTexture(currentSelection), 75, 300, 450, 450));
    ui.addButton(restartButton);
    ui.addButton(undoButton);
    ui.addButton(backButton);

    ui.render();
}

void Menu::handleEvent(sf::Event& event) {                                          // Handle the event based on the current menu state
    if (isMainMenuActive) {
        startButton->handleEvent(event, *window);
        quitButton->handleEvent(event, *window);
        leftArrowButton->handleEvent(event, *window);
        rightArrowButton->handleEvent(event, *window);
    } else if (isGameMenuActive) {
        restartButton->handleEvent(event, *window);
        undoButton->handleEvent(event, *window);
        backButton->handleEvent(event, *window);
    }
}

void Menu::handleInput(sf::Keyboard::Key key) {                                     // Handle the input based on the current menu state
    if (isGameMenuActive) {
        if (gridObject->isGameOver() && !gridObject->canMove()) {                   // Check if the game is over and add the game over UI elements
            if (!gameOverHandled) {
                ui.addGameObjectEnd(gameOver);
                ui.addTextEnd(gameOverText);
                gameOverHandled = true;
                std::cout << "Game over! UI elements added." << std::endl;
            }
            return;
        }
        gridObject->handleInput(key);
        cout << "Updating score text" << endl;
        ui.updateScoreText(std::to_string(gridObject->getScore()));
        cout<< "score" << gridObject->getScore() << endl;
        ui.setGrid(gridObject);
        ui.renderGame();

        if (gridObject->isGameWon() && !gameAlreadyWon) {                           // Check if the game is won and add the game win UI elements
            if (!gameWinHandled) {
                ui.addGameObjectEnd(gameWin);
                ui.addTextEnd(gameWinText);
                ui.addTextEnd(continueText);
                ui.render();
                gameWinHandled = true;
            }
            return;
        }
        if (gameWinHandled && (key == sf::Keyboard::Left || key == sf::Keyboard::Right || key == sf::Keyboard::Up || key == sf::Keyboard::Down)) {
            ui.removeGameObject(gameWin);
            ui.removeText(gameWinText);
            ui.removeText(continueText);
            ui.render();
            gameWinHandled = false;
            gameAlreadyWon = true;
        }

        if (gridObject->isGameOver() && !gridObject->canMove()) {
            if (!gameOverHandled) {
                ui.addGameObjectEnd(gameOver);
                ui.addTextEnd(gameOverText);
                gameOverHandled = true;
                std::cout << "Game over after input! UI elements added." << std::endl;
            }
        }
    }
}

void Menu::startButtonClicked() {                                                                                            // Handle the start button click event, start the game             
    std::cout << "Start button clicked" << std::endl;
    isMainMenuActive = false;
    isGameMenuActive = true;
    drawGame();
}

void Menu::quitButtonClicked() {
    std::cout << "Quit button clicked" << std::endl;
    exit(0);  // Properly terminate the application
}

void Menu::leftArrowClicked() {                                                                                             // Handle the left arrow click event, update the grid selection (carousel)
    std::cout << "Left arrow clicked" << std::endl;
    currentSelection = (currentSelection - 1 + gridOptions.size()) % gridOptions.size();
    update();
}

void Menu::rightArrowClicked() {                                                                                            // Handle the right arrow click event, update the grid selection (carousel)
    std::cout << "Right arrow clicked" << std::endl;
    currentSelection = (currentSelection + 1) % gridOptions.size();
    update();
}

string Menu::getGameGridTexture(int selection) {                                                                            // Get the grid texture based on the current selection
    switch (selection) {
        case 0: return GRID;
        case 1: return GRID1;
        case 2: return GRID2;
        case 3: return GRID3;
        case 4: return GRID4;
        default: return GRID;  
    }
}

void Menu::update() {                                                                                                       // Update the grid selection based on the current selection
    gridImage->setTexture( gridOptions[currentSelection]);
    ui.render();
}