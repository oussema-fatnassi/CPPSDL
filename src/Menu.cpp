// #include "Menu.hpp"

// Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(1), restartButton(nullptr), undoButton(nullptr) {       // Constructor
//     this->renderer = renderer;

//     gridOptions = {                                                                                                         // Grid options for the main menu
//         {IMAGE_GRID_3X3},
//         {IMAGE_GRID_4X4},
//         {IMAGE_GRID_5X5},
//         {IMAGE_GRID_6X6},
//         {IMAGE_GRID_8X8}
//     };
//     drawMainMenu();                                                                                                         // Draw the main menu            
//     isMainMenuActive = true;
//     isGameMenuActive = false;
// }

// Menu::~Menu() {}                                                                                                            // Destructor               

// void Menu::drawMainMenu() {                                                                                                 // Draw the main menu, add buttons, text and images   
//     isMainMenuActive = true;
//     isGameMenuActive = false;
//     font = TTF_OpenFont(FONT_PATH.c_str(), 60);                                                                             // Load the font for the main menu in different sizes
//     font1 = TTF_OpenFont(FONT_PATH.c_str(), 40);
//     font2 = TTF_OpenFont(FONT_PATH.c_str(), 20);
//     font3 = TTF_OpenFont(FONT_PATH.c_str(), 30);
//     Text* title = new Text(renderer, "2048", font, {113, 112, 107, 255}, 225, 50, 1);                                       // Create the texts for the main menu
//     Text* startText = new Text(renderer, "Start", font, {255, 255, 255, 255}, 225, 650, 1);
//     Text* quitText = new Text(renderer, "Quit", font, {255, 255, 255, 255}, 235, 740, 1);

//     gridImage = new GameObject(renderer, gridOptions[currentSelection], 150, 200, 300, 300);                                // Create the elements for the carousel

//     startButton = new Button(renderer, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 146, 650, 308, 80, [this] { startButtonClicked(); });             // Create the buttons for the main menu
//     quitButton = new Button(renderer, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 146, 750, 308, 80, [this] { quitButtonClicked(); });
//     leftArrowButton = new Button(renderer, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 310, 34, 74, [this] { leftArrowClicked(); });
//     rightArrowButton = new Button(renderer, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 465, 310, 34, 74, [this] { rightArrowClicked(); });
//     ui.addText(new Text(renderer, "Select Grid Size", font3, {113, 112, 107, 255}, 190, 560, 1));                          // Add the text and game objects to the UI for rendering

//     ui.addButton(startButton);                                                                                              // Add the buttons, text and images to the ui object for rendering
//     ui.addButton(quitButton);
//     ui.addButton(leftArrowButton);
//     ui.addButton(rightArrowButton);
//     ui.addText(title);
//     ui.addText(startText);
//     ui.addText(quitText);
//     ui.addText(gridText);
//     ui.addGameObject(gridImage);
//     ui.render();                                                                                                            // Render the main menu
// }

// void Menu::drawGame() {                                                                                                     // Draw the game screen, add buttons, text and images
//     isMainMenuActive = false;
//     isGameMenuActive = true;
//     ui.clear();                                                                                                             // Clear the UI elements from the main menu
//     gameOver = new GameObject(renderer, GAME_OVER, 75, 300, 450, 450);
//     gameWin = new GameObject(renderer, GAME_WIN, 75, 300, 450, 450);

//     gameOverText = new Text(renderer, "GAME OVER!", font, {113, 112, 107, 255}, 135, 480, 1);
//     gameWinText = new Text(renderer, "YOU WON!", font, {113, 112, 107, 255}, 155, 450, 1);
//     continueText = new Text(renderer, "Move to continue", font2, {113, 112, 107, 255}, 220, 530, 1);

//     switch (currentSelection) {                                                                                             // Create the grid object based on the current selection
//         case 0: gridObject = new Grid(3); break;
//         case 1: gridObject = new Grid(4); break;
//         case 2: gridObject = new Grid(5); break;
//         case 3: gridObject = new Grid(6); break;
//         case 4: gridObject = new Grid(8); break;
//         default: gridObject = new Grid(4); break;
//     }
//     ui.setGrid(gridObject);                                                                                                 // Set the grid object in the UI

//     restartButton = new Button(renderer, RESTART_BUTTON_NORMAL, RESTART_BUTTON_HOVER, RESTART_BUTTON_PRESSED, 465, 200, 50, 50, [this] {  // Create the buttons to restart the game
//         gameAlreadyWon = false; 
//         gridObject->reset();
//         ui.updateScoreText("0"); 
//         ui.setGrid(gridObject); 
//         if (gameOverHandled) {                                                                                             // Remove the game over UI elements if present
//             ui.removeGameObject(gameOver);
//             ui.removeText(gameOverText);
//             gameOverHandled = false;
//             std::cout << "Game restarted, game over UI elements removed." << std::endl;
//         }
//         ui.clear();
//         drawGame();
//     });

//     undoButton = new Button(renderer, UNDO_BUTTON_NORMAL, UNDO_BUTTON_HOVER, UNDO_BUTTON_PRESSED, 365, 200, 50, 50, [this] {        // Create the buttons to undo the last move
//         gridObject->undo(); 
//         ui.setGrid(gridObject);                                                                                             // Update the UI with the undone grid state
//         ui.renderGame();                                                                                                    // Re-render the grid to reflect the undo
//         ui.updateScoreText(to_string(gridObject->getScore()));                                                              // Update the score text
//     });

//     backButton = new Button(renderer, BACK_BUTTON_NORMAL, BACK_BUTTON_HOVER, BACK_BUTTON_PRESSED, 230, 770, 135, 80, [this] {         // Create the back button to return to the main menu
//         if (gridObject) {
//             delete gridObject;  
//             gridObject = nullptr;
//         }

//         ui.clear();  
//         isMainMenuActive = true;
//         isGameMenuActive = false;
//         drawMainMenu();                                                                                                    // Draw the main menu
//     });
    
//     ui.addText(new Text(renderer, "SCORE", font2, {113, 112, 107, 255}, 405, 105, 1));                                      // Add the text and game objects to the UI for rendering
//     ui.addText(new Text(renderer, "0", font1, {251, 248, 239, 255}, 385, 120, 1111));
//     ui.addText(new Text(renderer, "2048", font, {113, 112, 107, 255}, 50, 100, 2));
//     ui.addText(new Text(renderer, "Back", font3, {255, 255, 255, 255}, 265, 785, 1));
//     ui.addGameObject(new GameObject(renderer, SCORE, 350, 100, 180, 80));
//     ui.addGameObject(new GameObject(renderer, getGameGridTexture(currentSelection), 75, 300, 450, 450)) ;    
//     ui.addButton(restartButton);
//     ui.addButton(undoButton);
//     ui.addButton(backButton);

//     ui.render();                                                                                                            // Render the game screen
// }

// void Menu::handleEvent(SDL_Event* event) {                                                                                  // Handle events for the main menu and game screen based on the event type
//     if(isMainMenuActive){
//         startButton->handleEvent(event);
//         quitButton->handleEvent(event);
//         leftArrowButton->handleEvent(event);
//         rightArrowButton->handleEvent(event);
//     } else if (isGameMenuActive){
//         restartButton->handleEvent(event);
//         undoButton->handleEvent(event);
//         backButton->handleEvent(event);
//     }
// }

// void Menu::handleInput(SDL_Keycode key) {                                                                                   // Handle input for the game screen based on the key pressed                       
// if(isGameMenuActive){
//     if (gridObject->isGameOver() && !gridObject->canMove()) {
//         if (!gameOverHandled) {
//             ui.addGameObjectEnd(gameOver);
//             ui.addTextEnd(gameOverText);
//             gameOverHandled = true;
//             std::cout << "Game over! UI elements added." << std::endl;
//         }
//         return;
//     }

//     if (gridObject->isGameWon() && !gameAlreadyWon) {                                                                          // Check if the game is won
//         if (!gameWinHandled) {
//             ui.addGameObjectEnd(gameWin);
//             ui.addTextEnd(gameWinText);
//             ui.addTextEnd(continueText);
//             ui.render();
//             gameWinHandled = true;
//         }
//         if (key == SDLK_LEFT || key == SDLK_RIGHT || key == SDLK_UP || key == SDLK_DOWN) {                                     // If the user presses an arrow key, remove the game win UI elements
//             gameAlreadyWon = true;  
//             ui.removeGameObject(gameWin);
//             ui.removeText(gameWinText);
//             ui.removeText(continueText);
//             ui.render();
//             return;
//         }
//         return;                                                                                                                // Skip other inputs until the user presses an arrow key
//     }

//     gridObject->handleInput(key);                                                                                              // Process input if the game is not over or won
//     ui.updateScoreText(std::to_string(gridObject->getScore()));
//     ui.setGrid(gridObject);
//     ui.renderGame();

//     if (gridObject->isGameOver() && !gridObject->canMove()) {                                                                   // Re-check if the game is over after processing input
//         if (!gameOverHandled) {
//             ui.addGameObjectEnd(gameOver);
//             ui.addTextEnd(gameOverText);
//             gameOverHandled = true;
//             std::cout << "Game over after input! UI elements added." << std::endl;
//             }
//         }
//     }
// }

// void Menu::startButtonClicked() {                                                                                           // Handle the start button click event, draw the game screen
//     std::cout << "Start button clicked" << std::endl;
//     isMainMenuActive = false;
//     isGameMenuActive = true;
//     drawGame();
// }

// void Menu::quitButtonClicked() {                                                                                            // Handle the quit button click event, quit the game
//     std::cout << "Quit button clicked" << std::endl;
//     SDL_Quit();
//     exit(0);
// }

// void Menu::leftArrowClicked() {                                                                                             // Handle the left arrow click event, update the grid selection (carousel)
//     std::cout << "Left arrow clicked" << std::endl;
//     currentSelection = (currentSelection - 1 + gridOptions.size()) % gridOptions.size();
//     update();
// }

// void Menu::rightArrowClicked() {                                                                                            // Handle the right arrow click event, update the grid selection (carousel)
//     std::cout << "Right arrow clicked" << std::endl;
//     currentSelection = (currentSelection + 1) % gridOptions.size();
//     update();
// }

// void Menu::update() {                                                                                                       // Update the grid selection based on the current selection
//     gridImage->setTexture(renderer, gridOptions[currentSelection]);
//     ui.render();
// }

// string Menu::getGameGridTexture(int selection) {                                                                            // Get the grid texture based on the current selection
//     switch (selection) {
//         case 0: return GRID;
//         case 1: return GRID1;
//         case 2: return GRID2;
//         case 3: return GRID3;
//         case 4: return GRID4;
//         default: return GRID;  
//     }
// }