#include "Button.hpp"
#include "Menu.hpp"
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "2048 Game");                      // Create a window with SFML

    UI ui(window);                                                                      // Create a UI object with SFML's window
    Menu menu(window);                                                                  // Create a Menu object with SFML's window

    bool quit = false;
    sf::Event event;

    menu.drawMainMenu();                                                                // Draw the main menu

    while (window.isOpen()) {                                                           // Main game loop
        window.clear(sf::Color(251, 248, 239, 255));                                    // Clear the window     

        menu.update();                                                                  // Update the menu        
        window.display();                                                               // Display the window

        while (window.pollEvent(event)) {                                               // Poll events from the window to handle input          
            if (event.type == sf::Event::Closed) {                                      // Close the window if the close button is clicked
                window.close();
                quit = true;
            }
            else if (event.type == sf::Event::MouseMoved ||                             // Handle mouse events
                     event.type == sf::Event::MouseButtonPressed || 
                     event.type == sf::Event::MouseButtonReleased) {
                menu.handleEvent(event);                            
            }
            else if (event.type == sf::Event::KeyPressed) {                             // Handle key events
                menu.handleInput(event.key.code);  
            }
        }
    }
    return 0;
}