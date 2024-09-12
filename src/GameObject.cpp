#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(sf::RenderWindow& window, int value, int x, int y, int width, int height)            // Constructor with value (for tiles)
    : window(window), x(x), y(y), width(width), height(height) {

    if (value == 0) {
        return;
    }

    std::string imagePath = getImagePathToValue(value);
    loadTexture(imagePath);
}

GameObject::GameObject(sf::RenderWindow& window, const std::string& imagePath, int x, int y, int width, int height)       // Constructor without value (for images, buttons)
    : window(window), x(x), y(y), width(width), height(height) {

    loadTexture(imagePath);
}

GameObject::~GameObject() {}

void GameObject::render() {                                                                                 // Render method for GameObject 
    window.draw(sprite); 
}

std::string GameObject::getImagePathToValue(int value) {                                                    // Get the image path based on the value            
    if (value > 2048) {
        return "../assets/images/other.png";                                                                // Path for other values
    }
    return "../assets/images/" + std::to_string(value) + ".png";                                            // Path for specific values
}

void GameObject::loadTexture(const std::string& imagePath) {                                                // Load the texture for the GameObject
    texture = ResourceManager::getInstance().getTexture(imagePath);                                         // Get texture from resource manager
    if (!texture) {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
        return;
    }

    sprite.setTexture(*texture);                                                                            // Set the texture for the sprite
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));                                       // Set the position
    sprite.setScale(                                                                                        // Scale the sprite to fit the desired width and height
        static_cast<float>(width) / texture->getSize().x, 
        static_cast<float>(height) / texture->getSize().y
    );  
}

void GameObject::setTexture(const std::string& imagePath) {                                                 // Set the texture for the GameObject        
    loadTexture(imagePath); 
}

int GameObject::getX() const {
    return x;
}

int GameObject::getY() const {
    return y;
}

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}
