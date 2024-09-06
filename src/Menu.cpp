#include "Menu.hpp"
#include <iostream>
#include "Assets.hpp"
using namespace std;

Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(0){
    this->renderer = renderer;
    drawMainMenu();
}

Menu::~Menu() {
}

void Menu::drawMainMenu(){

    font = TTF_OpenFont(FONT_PATH.c_str(), 60);
    font1 = TTF_OpenFont(FONT_PATH.c_str(), 40);
    Text* title = new Text(renderer, "2048", font, {113, 112, 107, 255}, 225, 50);
    Text* startText = new Text(renderer, "START", font, {255, 255, 255, 255}, 225, 650);
    Text* quitText = new Text(renderer, "QUIT", font, {255, 255, 255, 255}, 225, 750);
    Text* classic = new Text(renderer, "Classic 4x4", font1, {113, 112, 107, 255}, 190, 510);
    startButton = new Button(renderer, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 146, 650, 308, 80, [this]{ startButtonClicked(); });
    quitButton = new Button(renderer, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 146, 750, 308, 80, [this]{ quitButtonClicked(); });
    leftArrowButton = new Button(renderer, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 500, 34, 74, [this] {leftArrowClicked(); });
    rightArrowButton = new Button(renderer, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 450, 500, 34, 74, [this](){ rightArrowClicked(); });
    GameObject* imageBackground4x4 = new GameObject(renderer, IMAGE_GRID_4X4, 150, 150, 300, 300);

    ui.addButton(startButton);
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);
    ui.addText(title);
    ui.addText(startText);
    ui.addText(quitText);
    ui.addText(classic);
    ui.addGameObject(imageBackground4x4);
    ui.render();
}

void Menu::handleEvent(SDL_Event* event) {
    startButton->handleEvent(event);
    quitButton->handleEvent(event);
    leftArrowButton->handleEvent(event);
    rightArrowButton->handleEvent(event);
}

void Menu::startButtonClicked() {
    std::cout << "Start button clicked" << std::endl;
}

void Menu::quitButtonClicked() {
    std::cout << "Quit button clicked" << std::endl;
    SDL_QUIT;
    exit(0);
}

void Menu::leftArrowClicked() {
    std::cout << "Left arrow clicked" << std::endl;
}

void Menu::rightArrowClicked() {
    std::cout << "Right arrow clicked" << std::endl;
}

void Menu::update() {
    ui.render(); 
}
