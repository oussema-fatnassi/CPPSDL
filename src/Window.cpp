#include "Window.hpp"
#include <iostream>

Window::Window(const std::string& title, int width, int height) 
    : title(title), width(width), height(height), closed(false) {
    closed = !init();
}

Window::~Window() {
    // SFML handles cleanup internally, no need to manually destroy textures or windows
}

bool Window::init() {
    // Create the window
    window.create(sf::VideoMode(width, height), title);
    if (!window.isOpen()) {
        std::cerr << "Failed to create SFML window" << std::endl;
        return false;
    }

    return true;
}

void Window::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            closed = true;
            window.close();
        }
    }
}

bool Window::isClosed() const {
    return closed;
}

void Window::clear() {
    window.clear(sf::Color::Black);  // Clear the window with black color
}

void Window::present() {
    window.display();  // Display the current frame
}

void Window::renderImage(const std::string& imagePath, int x, int y, int width, int height) {
    // Load the texture from file
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return;
    }

    // Set up the sprite with the texture and position it
    sprite.setTexture(texture);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    sprite.setScale(static_cast<float>(width) / texture.getSize().x, static_cast<float>(height) / texture.getSize().y);

    // Draw the sprite to the window
    window.draw(sprite);
}

sf::RenderWindow& Window::getRenderWindow() {
    return window;
}