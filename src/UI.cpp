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
    for (auto& gameObject : gameObjects) {
        delete gameObject;
    }
}

void UI::addButton(Button* button) {
    buttons.push_back(button);
}

void UI::addText(Text* text) {
    texts.push_back(text);
}

void UI::addGameObject(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
}

void UI::render() {
    for (Button* button : buttons) {
        button->render(renderer);
    }

    for (Text* text : texts) {
        text->render(renderer);
    }

    for (GameObject* gameObject : gameObjects) {
        gameObject->render(renderer);
    }
}

void UI:: clear() {
    buttons.clear();
    texts.clear();
    gameObjects.clear();
}