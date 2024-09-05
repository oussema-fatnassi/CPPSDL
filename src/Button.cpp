#include "Button.hpp"
#include <iostream>

Button::Button(SDL_Renderer* renderer, const std::string& normalImage, const std::string& hoverImage, const std::string& pressedImage, 
               int x, int y, int width, int height, std::function<void()> onClickCallback)
    : GameObject(renderer, normalImage, x, y, width, height), 
      normalImage(normalImage), hoverImage(hoverImage), pressedImage(pressedImage), 
      currentState(ButtonState::NORMAL), onClickCallback(onClickCallback) {}

void Button::handleEvent(SDL_Event* event) {
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool inside = (mouseX > this->getX() && mouseX < this->getX() + this->getWidth() && mouseY > this->getY() && mouseY < this->getY() + this->getHeight());

        if (!inside) {
            changeState(ButtonState::NORMAL);
        } else {
            switch (event->type) {
                case SDL_MOUSEMOTION:
                    changeState(ButtonState::HOVER);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    changeState(ButtonState::PRESSED);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (currentState == ButtonState::PRESSED) {
                        onClickCallback(); 
                    }
                    changeState(ButtonState::HOVER);
                    break;
            }
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    GameObject::render(renderer);  
}

void Button::changeState(ButtonState newState) {
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
            case ButtonState::NORMAL:
                loadTexture(renderer, normalImage);
                break;
            case ButtonState::HOVER:
                loadTexture(renderer, hoverImage);
                break;
            case ButtonState::PRESSED:
                loadTexture(renderer, pressedImage);
                break;
        }
    }
}
