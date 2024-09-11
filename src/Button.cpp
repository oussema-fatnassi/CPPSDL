#include "Button.hpp"

Button::Button(sf::RenderWindow& window, const std::string& normalImage, const std::string& hoverImage, const std::string& pressedImage,      // Constructor
               int x, int y, int width, int height, std::function<void()> onClickCallback)
    : GameObject(window, normalImage, x, y, width, height), 
      normalImage(normalImage), hoverImage(hoverImage), pressedImage(pressedImage), 
      currentState(ButtonState::NORMAL), onClickCallback(onClickCallback), window(window) {}

Button::~Button() {}                                        // Destructor

void Button::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (currentState == ButtonState::DISABLED) {
        return; // If button is disabled, do nothing
    }

    if (event.type == sf::Event::MouseMoved || 
        event.type == sf::Event::MouseButtonPressed || 
        event.type == sf::Event::MouseButtonReleased) {
        
        // Get the mouse position relative to the window
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Check if the mouse is inside the button's bounds
        bool inside = (mousePos.x > this->getX() && mousePos.x < this->getX() + this->getWidth() && 
                       mousePos.y > this->getY() && mousePos.y < this->getY() + this->getHeight());

        if (!inside) {
            changeState(ButtonState::NORMAL);  // Mouse is outside the button
        } else {
            switch (event.type) {
                case sf::Event::MouseMoved:  // Mouse is hovering over the button
                    changeState(ButtonState::HOVER);
                    break;
                case sf::Event::MouseButtonPressed:  // Mouse button is pressed
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        changeState(ButtonState::PRESSED);
                    }
                    break;
                case sf::Event::MouseButtonReleased:  // Mouse button is released
                    if (event.mouseButton.button == sf::Mouse::Left && currentState == ButtonState::PRESSED) {
                        onClickCallback();  // Trigger callback when button is clicked
                        changeState(ButtonState::HOVER);
                    }
                    break;
            }
        }
    }
}

void Button::render() {               // Render method
    GameObject::render();  
}

void Button::disable() {                                    // Disable method, change state to disabled
    currentState = ButtonState::DISABLED;  
}

void Button::changeState(ButtonState newState) {            // Change state method and load texture based on state
    if (currentState != newState) {
        currentState = newState;
        switch (newState) {
            case ButtonState::NORMAL:
                loadTexture(normalImage);
                break;
            case ButtonState::HOVER:
                loadTexture(hoverImage);
                break;
            case ButtonState::PRESSED:
                loadTexture(pressedImage);
                break;
        }
    }
}
