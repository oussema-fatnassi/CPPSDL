#include "UI.hpp"
#include <iostream>

UI::UI(SDL_Renderer* renderer) : renderer(renderer) {}

UI::~UI() {
    for (auto& button : buttons) {
        delete button;
    }
    for (auto& text : texts) {
        delete text;
    }
}

void UI::addButton(Button* button) {
    buttons.push_back(button);
}

void UI::addText(Text* text) {
    texts.push_back(text);
}

void UI::render() {
    for (Button* button : buttons) {
        button->render(renderer);
    }

    for (Text* text : texts) {
        text->render(renderer);
    }
}
