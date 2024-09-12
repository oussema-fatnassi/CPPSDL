#include "Window.hpp"
#include <iostream>

Window::Window(const std::string& title, int width, int height)                     // Constructor
    : title(title), width(width), height(height), closed(false) {
    closed = !init();
}

Window::~Window() {}

bool Window::init() {                                                               // Initialize the window                    
    window.create(sf::VideoMode(width, height), title);
    if (!window.isOpen()) {
        std::cerr << "Failed to create SFML window" << std::endl;
        return false;
    }

    return true;
}

void Window::pollEvents() {                                                         // Poll events from the window to manage input           
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

void Window::clear() {                                                              // Clear the window           
    window.clear(sf::Color::Black);  
}

void Window::present() {                                                            // Display the window
    window.display();  
}

void Window::renderImage(const std::string& imagePath, int x, int y, int width, int height) {
    if (!texture.loadFromFile(imagePath)) {                                         // Load the texture from the image path
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    sprite.setScale(static_cast<float>(width) / texture.getSize().x, static_cast<float>(height) / texture.getSize().y);

    window.draw(sprite);
}

sf::RenderWindow& Window::getRenderWindow() {                                       // Get the SFML render window
    return window;
}