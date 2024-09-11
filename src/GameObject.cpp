#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(sf::RenderWindow& window, int value, int x, int y, int width, int height) 
    : window(window), x(x), y(y), width(width), height(height) {

    if (value == 0) {
        return;
    }

    std::string imagePath = getImagePathToValue(value);
    loadTexture(imagePath);
}

GameObject::GameObject(sf::RenderWindow& window, const std::string& imagePath, int x, int y, int width, int height) 
    : window(window), x(x), y(y), width(width), height(height) {

    loadTexture(imagePath);
}

GameObject::~GameObject() {
    // SFML handles cleanup internally, no need to manually destroy textures or sprites
}

void GameObject::render() {
    window.draw(sprite); // Draw the sprite to the window
}

std::string GameObject::getImagePathToValue(int value) {
    if (value > 2048) {
        return "../assets/images/other.svg"; // Path for other values
    }
    return "../assets/images/" + std::to_string(value) + ".svg"; // Path for specific values
}

void GameObject::loadTexture(const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return;
    }
    sprite.setTexture(texture);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    sprite.setScale(static_cast<float>(width) / texture.getSize().x, static_cast<float>(height) / texture.getSize().y);
}

void GameObject::setTexture(const std::string& imagePath) {
    loadTexture(imagePath); // Re-load the texture with the new image path
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
