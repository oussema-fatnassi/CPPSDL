#include "Menu.hpp"

Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(1), restartButton(nullptr), undoButton(nullptr) {       // Constructor
    this->renderer = renderer;

    gridOptions = {                                                                                                         // Grid options for the main menu
        {IMAGE_GRID_3X3, "Tiny 3x3"},
        {IMAGE_GRID_4X4, "Classic 4x4"},
        {IMAGE_GRID_5X5, "Big 5x5"},
        {IMAGE_GRID_6X6, "Larger 6x6"},
        {IMAGE_GRID_8X8, "Huge 8x8"}
    };

    drawMainMenu();                                                                                                         // Draw the main menu            
}

Menu::~Menu() {}                                                                                                            // Destructor               

void Menu::drawMainMenu() {                                                                                                 // Draw the main menu, add buttons, text and images   
    font = TTF_OpenFont(FONT_PATH.c_str(), 60);                                                                             // Load the font for the main menu in different sizes
    font1 = TTF_OpenFont(FONT_PATH.c_str(), 40);
    font2 = TTF_OpenFont(FONT_PATH.c_str(), 20);
    Text* title = new Text(renderer, "2048", font, {113, 112, 107, 255}, 225, 50, 1);                                       // Create the texts for the main menu
    Text* startText = new Text(renderer, "START", font, {255, 255, 255, 255}, 225, 650, 1);
    Text* quitText = new Text(renderer, "QUIT", font, {255, 255, 255, 255}, 225, 750, 1);

    gridImage = new GameObject(renderer, gridOptions[currentSelection].first, 150, 150, 300, 300);                          // Create the elements for the carousel
    gridText = new Text(renderer, gridOptions[currentSelection].second, font1, {113, 112, 107, 255}, 190, 510, 1);

    startButton = new Button(renderer, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 146, 650, 308, 80, [this] { startButtonClicked(); });             // Create the buttons for the main menu
    quitButton = new Button(renderer, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 146, 750, 308, 80, [this] { quitButtonClicked(); });
    leftArrowButton = new Button(renderer, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 500, 34, 74, [this] { leftArrowClicked(); });
    rightArrowButton = new Button(renderer, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 450, 500, 34, 74, [this] { rightArrowClicked(); });

    ui.addButton(startButton);                                                                                              // Add the buttons, text and images to the ui object for rendering
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);
    ui.addText(title);
    ui.addText(startText);
    ui.addText(quitText);
    ui.addText(gridText);
    ui.addGameObject(gridImage);
    ui.render();                                                                                                            // Render the main menu
}

void Menu::drawGame() {                                                                                                     // Draw the game screen, add buttons, text and images
    ui.clear();                                                                                                             // Clear the UI elements from the main menu

    gameOver = new GameObject(renderer, GAME_OVER, 75, 300, 450, 450);
    gameWin = new GameObject(renderer, GAME_WIN, 75, 300, 450, 450);

    gameOverText = new Text(renderer, "GAME OVER!", font, {113, 112, 107, 255}, 135, 480, 1);
    gameWinText = new Text(renderer, "YOU WON!", font, {113, 112, 107, 255}, 155, 450, 1);
    continueText = new Text(renderer, "Move to continue", font2, {113, 112, 107, 255}, 220, 530, 1);

    switch (currentSelection) {                                                                                             // Create the grid object based on the current selection
        case 0: gridObject = new Grid(3); break;
        case 1: gridObject = new Grid(4); break;
        case 2: gridObject = new Grid(5); break;
        case 3: gridObject = new Grid(6); break;
        case 4: gridObject = new Grid(8); break;
        default: gridObject = new Grid(4); break;
    }
    ui.setGrid(gridObject);                                                                                                 // Set the grid object in the UI
    restartButton = new Button(renderer, RESTART_BUTTON_NORMAL, RESTART_BUTTON_HOVER, RESTART_BUTTON_PRESSED, 465, 200, 50, 50, [this] {    // Create the buttons to restart the game
        gridObject->reset(); 
        ui.setGrid(gridObject);                                                                                             // Update the UI with the reset grid
        ui.renderGame();                                                                                                    // Re-render the grid to reflect the reset
        ui.updateScoreText("0");                                                                                            // Reset the score text

        if (gameOverHandled) {                                                                                              // Remove the game over UI elements if present
            ui.removeGameObject(gameOver);
            ui.removeText(gameOverText);
            gameOverHandled = false;
            std::cout << "Game restarted, game over UI elements removed." << std::endl;
        }
    });

    undoButton = new Button(renderer, UNDO_BUTTON_NORMAL, UNDO_BUTTON_HOVER, UNDO_BUTTON_PRESSED, 365, 200, 50, 50, [this] {        // Create the buttons to undo the last move
        gridObject->undo(); 
        ui.setGrid(gridObject);                                                                                             // Update the UI with the undone grid state
        ui.renderGame();                                                                                                    // Re-render the grid to reflect the undo
        ui.updateScoreText(to_string(gridObject->getScore()));                                                              // Update the score text
    });
    
    ui.addText(new Text(renderer, "SCORE", font2, {113, 112, 107, 255}, 405, 105, 1));                                      // Add the text and game objects to the UI for rendering
    ui.addText(new Text(renderer, "0", font1, {251, 248, 239, 255}, 405, 120, 1111));
    ui.addText(new Text(renderer, "2048", font, {113, 112, 107, 255}, 50, 100, 2));
    ui.addGameObject(new GameObject(renderer, SCORE, 350, 100, 180, 80));
    ui.addGameObject(new GameObject(renderer, getGameGridTexture(currentSelection), 75, 300, 450, 450)) ;    
    ui.addButton(restartButton);
    ui.addButton(undoButton);

    ui.render();                                                                                                            // Render the game screen
}

void Menu::handleEvent(SDL_Event* event) {                                                                                  // Handle events for the main menu and game screen based on the event type
    startButton->handleEvent(event);
    quitButton->handleEvent(event);
    leftArrowButton->handleEvent(event);
    rightArrowButton->handleEvent(event);
    if (restartButton != nullptr) {
        restartButton->handleEvent(event);
    }
    if (undoButton != nullptr) {
        undoButton->handleEvent(event);
    }
}

void Menu::handleInput(SDL_Keycode key) {                                                                                   // Handle input for the game screen
    if (gridObject->isGameOver() && !gridObject->canMove()) {                                                               // Check if the game is over, and handle game over state only once
        if (!gameOverHandled) {
            ui.addGameObjectEnd(gameOver);
            ui.addTextEnd(gameOverText);
            gameOverHandled = true; 
            std::cout << "Game over! UI elements added." << std::endl;
        }
        return;                                                                                                             // Do not process input if the game is over
    }

    if (gridObject->isGameWon()) {                                                                                          // Check if the game is won, and handle game won state only once
        ui.addGameObjectEnd(gameWin);
        ui.addTextEnd(gameWinText);
        ui.addTextEnd(continueText);
    }

    gridObject->handleInput(key);                                                                                           // Handle input for the grid object                                                                
    ui.setGrid(gridObject); 
    ui.renderGame(); 
    ui.updateScoreText(std::to_string(gridObject->getScore()));

    if (gridObject->isGameOver() && !gridObject->canMove()) {                                                               // Check if the game is over after input
        if (!gameOverHandled) {
            ui.addGameObjectEnd(gameOver);
            ui.addTextEnd(gameOverText);
            gameOverHandled = true;  
            std::cout << "Game over after input! UI elements added." << std::endl;
        }
    }
}

void Menu::startButtonClicked() {                                                                                           // Handle the start button click event, draw the game screen
    std::cout << "Start button clicked" << std::endl;
    drawGame();
}

void Menu::quitButtonClicked() {                                                                                            // Handle the quit button click event, quit the game
    std::cout << "Quit button clicked" << std::endl;
    SDL_Quit();
    exit(0);
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

void Menu::update() {                                                                                                       // Update the grid selection based on the current selection
    gridImage->setTexture(renderer, gridOptions[currentSelection].first);
    gridText->setText(gridOptions[currentSelection].second);
    ui.render();
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