#include "Menu.hpp"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : ui(renderer), currentSelection(0){
    this->renderer = renderer;
    drawMainMenu();
}

Menu::~Menu() {
}

void Menu::drawMainMenu(){

    startButton = new Button(renderer, "../assets/images/start.svg", "../assets/images/start_hover.svg", "../assets/images/start_pressed.svg", 100, 100, 308, 80, [this]{ startButtonClicked(); });

    quitButton = new Button(renderer, "../assets/images/quit.svg", "../assets/images/quit_hover.svg", "../assets/images/quit_pressed.svg", 100, 250, 308, 80, [this]{ quitButtonClicked(); });

    leftArrowButton = new Button(renderer, "../assets/images/left_arrow.svg", "../assets/images/left_arrow_hover.svg", "../assets/images/left_arrow_pressed.svg", 100, 400, 34, 74, [this] {leftArrowClicked(); });

    rightArrowButton = new Button(renderer, "../assets/images/right_arrow.svg", "../assets/images/right_arrow_hover.svg", "../assets/images/right_arrow_pressed.svg", 150, 400, 34, 74, [this](){ rightArrowClicked(); });

    ui.addButton(startButton);
    ui.addButton(quitButton);
    ui.addButton(leftArrowButton);
    ui.addButton(rightArrowButton);

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
