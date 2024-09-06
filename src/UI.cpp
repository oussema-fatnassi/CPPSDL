#include "UI.hpp"

UI::UI(SDL_Renderer* renderer) : renderer(renderer) {}

UI::~UI() {
    for (auto& button : buttons) {
        delete button;
    }
}

void UI::addButton(Button* button) {
    buttons.push_back(button);
}

void UI::render() {
    for (Button* button : buttons) {
        button->render(renderer);
    }
}