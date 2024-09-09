#include "Menu.hpp"
#include <iostream>
#include "Assets.hpp"
using namespace std;

Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(1), restartButton(nullptr), undoButton(nullptr) {
    this->renderer = renderer;

    gridOptions = {
        {IMAGE_GRID_3X3, "Tiny 3x3"},
        {IMAGE_GRID_4X4, "Classic 4x4"},
        {IMAGE_GRID_5X5, "Big 5x5"},
        {IMAGE_GRID_6X6, "Larger 6x6"},
        {IMAGE_GRID_8X8, "Huge 8x8"}
    };

    drawMainMenu();
}

Menu::~Menu() {
}

void Menu::drawMainMenu() {
    font = TTF_OpenFont(FONT_PATH.c_str(), 60);
    font1 = TTF_OpenFont(FONT_PATH.c_str(), 40);
    Text* title = new Text(renderer, "2048", font, {113, 112, 107, 255}, 225, 50);
    Text* startText = new Text(renderer, "START", font, {255, 255, 255, 255}, 225, 650);
    Text* quitText = new Text(renderer, "QUIT", font, {255, 255, 255, 255}, 225, 750);

    gridImage = new GameObject(renderer, gridOptions[currentSelection].first, 150, 150, 300, 300);
    gridText = new Text(renderer, gridOptions[currentSelection].second, font1, {113, 112, 107, 255}, 190, 510);

    startButton = new Button(renderer, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 146, 650, 308, 80, [this] { startButtonClicked(); });
    quitButton = new Button(renderer, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 146, 750, 308, 80, [this] { quitButtonClicked(); });
    leftArrowButton = new Button(renderer, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 500, 34, 74, [this] { leftArrowClicked(); });
    rightArrowButton = new Button(renderer, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 450, 500, 34, 74, [this] { rightArrowClicked(); });

    ui.addButton(startButton);
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);
    ui.addText(title);
    ui.addText(startText);
    ui.addText(quitText);
    ui.addText(gridText);
    ui.addGameObject(gridImage);
    ui.render();

}

void Menu::handleEvent(SDL_Event* event) {
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

void Menu::handleInput(SDL_Keycode key) {
    switch (key) {
        case SDLK_DOWN:
            gridObject->move(1, 0);
            break;
        case SDLK_UP:
            gridObject->move(-1, 0);
            break;
        case SDLK_LEFT:
            gridObject->move(0, -1);
            break;
        case SDLK_RIGHT:
            gridObject->move(0, 1);
            break;
    }
    gridObject->addRandomNumber(); // Add a random number after each move
    ui.setGrid(gridObject); // Ensure the UI has the latest grid state
    ui.renderGame(); // Render the updated grid
}


void Menu::startButtonClicked() {
    std::cout << "Start button clicked" << std::endl;
    drawGame();
}

void Menu::quitButtonClicked() {
    std::cout << "Quit button clicked" << std::endl;
    SDL_Quit();
    exit(0);
}

void Menu::leftArrowClicked() {
    std::cout << "Left arrow clicked" << std::endl;
    currentSelection = (currentSelection - 1 + gridOptions.size()) % gridOptions.size();
    update();
}

void Menu::rightArrowClicked() {
    std::cout << "Right arrow clicked" << std::endl;
    currentSelection = (currentSelection + 1) % gridOptions.size();
    update();
}

void Menu::update() {
    gridImage->setTexture(renderer, gridOptions[currentSelection].first);
    gridText->setText(gridOptions[currentSelection].second);
    ui.render();
}

void Menu::drawGame() {
    ui.clear();

    gridObject = new Grid(4);
    ui.setGrid(gridObject);
    restartButton = new Button(renderer, RESTART_BUTTON_NORMAL, RESTART_BUTTON_HOVER, RESTART_BUTTON_PRESSED, 465, 200, 50, 50, [this] { cout << "Restart button clicked" << endl; });
    undoButton = new Button(renderer, UNDO_BUTTON_NORMAL, UNDO_BUTTON_HOVER, UNDO_BUTTON_PRESSED, 365, 200, 50, 50, [] { cout << "Undo button clicked" << endl; });
    ui.addGameObject(new GameObject(renderer, SCORE, 350, 100, 180, 80));
    ui.addGameObject(new GameObject(renderer, getGameGridTexture(currentSelection), 75, 300, 450, 450)) ;    
    ui.addText(new Text(renderer, "2048", font1, {113, 112, 107, 255}, 50, 100));
    ui.addText(new Text(renderer, "SCORE", font1, {113, 112, 107, 255}, 405, 105));
    ui.addText(new Text(renderer, "0", font1, {251, 248, 239, 255}, 405, 120));

    ui.addButton(restartButton);

    ui.addButton(undoButton);
    ui.render();
}

string Menu::getGameGridTexture(int selection) {
    switch (selection) {
        case 0: return GRID;
        case 1: return GRID1;
        case 2: return GRID2;
        case 3: return GRID3;
        case 4: return GRID4;
        default: return GRID;  
    }
}
