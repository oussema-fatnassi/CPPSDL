#include "Menu.hpp"
#include <iostream>
#include "Assets.hpp"

Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(0){
    this->renderer = renderer;
    drawMainMenu();
}

Menu::~Menu() {
}

void Menu::drawMainMenu(){

    font = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", 60);
    Text* title = new Text(renderer, "Game Title", font, {255, 255, 255, 255}, 100, 50);
    startButton = new Button(renderer, START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 100, 100, 308, 80, [this]{ startButtonClicked(); });
    quitButton = new Button(renderer, QUIT_BUTTON_NORMAL, QUIT_BUTTON_HOVER, QUIT_BUTTON_PRESSED, 100, 250, 308, 80, [this]{ quitButtonClicked(); });
    leftArrowButton = new Button(renderer, LEFT_ARROW_NORMAL, LEFT_ARROW_HOVER, LEFT_ARROW_PRESSED, 100, 400, 34, 74, [this] {leftArrowClicked(); });
    rightArrowButton = new Button(renderer, RIGHT_ARROW_NORMAL, RIGHT_ARROW_HOVER, RIGHT_ARROW_PRESSED, 150, 400, 34, 74, [this](){ rightArrowClicked(); });

    ui.addButton(startButton);
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);
    ui.addText(title);
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
