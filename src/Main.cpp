#include "Button.hpp"
#include <iostream>
#include "Menu.hpp"
#include "Window.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 900);                       // Create a window
    UI ui(window.getRenderer());                                // Create a UI object
    Menu menu(window.getRenderer());                            // Create a Menu object     

    bool quit = false;
    SDL_Event event;

    menu.drawMainMenu();                                        // Draw the main menu

    while (!quit) {                                             // Main game loop
        window.clear();                                         // Clear the window
        menu.update();                                          // Update the menu

        SDL_SetRenderDrawColor(window.getRenderer(), 251, 248, 239, 255);       // Set the render draw color          
        window.present();                                        // Present the window              

        while (SDL_PollEvent(&event)) {                         // Poll events
            if (event.type == SDL_QUIT) {                       // If quit event, set quit to true         
                quit = true;
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {         // Handle mouse events
                menu.handleEvent(&event);
            } else if (event.type == SDL_KEYDOWN) {             // Handle key events
                menu.handleInput(event.key.keysym.sym);         // Pass key events to the Menu
            }
        }

        SDL_Delay(10);                                          // Delay to reduce CPU usage
    }

    return 0;
}