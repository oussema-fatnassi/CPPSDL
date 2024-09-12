// #include "Window.hpp"
// #include "GameObject.hpp"
// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include "Assets.hpp"
// #include "Button.hpp"

// int main() {
//     // Create a Window object with title "SFML Window" and dimensions 600x800
//     Window window("SFML Window", 600, 800);

//     // Create a GameObject with an image
//     GameObject gameObject(window.getRenderWindow(),IMAGE_GRID_3X3, 75, 100, 450, 450);
//     Button button(window.getRenderWindow(), START_BUTTON_NORMAL, START_BUTTON_HOVER, START_BUTTON_PRESSED, 250, 600, 100, 50, [&gameObject]() { gameObject.setTexture(IMAGE_GRID_4X4); });

//     // Main loop
//     while (!window.isClosed()) {
//         // Poll events (e.g., for closing the window)
//         window.pollEvents();

//         // Clear the window
//         window.clear();

//         // Render the GameObject
//         gameObject.render();
//         button.render();

//         // Display the rendered frame
//         window.present();
//     }

//     return 0;
// }


// // TEXT TESTING
// #include "Text.hpp"
// #include "Window.hpp"
// #include <iostream>
// #include "Assets.hpp"


// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Example");
    
//     // Load a font from file
//     sf::Font font;
//     if (!font.loadFromFile(FONT_PATH)) {
//         std::cerr << "Failed to load font!" << std::endl;
//         return -1;
//     }
    
//     // Create a Text object
//     Text text(window, "Hello, SFML!", font, sf::Color::White, 100, 100, 1);

//     // Main loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         text.render();    // Render the text
//         window.display();
//     }

//     return 0;
// }




#include "Button.hpp"
#include "Menu.hpp"
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
    // Create a window with SFML
    sf::RenderWindow window(sf::VideoMode(600, 900), "2048 Game");

    UI ui(window);                                // Create a UI object with SFML's window
    Menu menu(window);                            // Create a Menu object with SFML's window

    bool quit = false;
    sf::Event event;

    menu.drawMainMenu();                          // Draw the main menu

    while (window.isOpen()) {                     // Main game loop
        // Clear the window
        window.clear(sf::Color(251, 248, 239, 255));

        // Update the menu
        menu.update();

        // Present/render the updated window
        window.display();

        // Poll events
        while (window.pollEvent(event)) {
            // If quit event, close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                quit = true;
            }
            // Handle mouse events
            else if (event.type == sf::Event::MouseMoved || 
                     event.type == sf::Event::MouseButtonPressed || 
                     event.type == sf::Event::MouseButtonReleased) {
                menu.handleEvent(event);  // Pass mouse events to Menu
            }
            // Handle key events
            else if (event.type == sf::Event::KeyPressed) {
                menu.handleInput(event.key.code);  // Pass key events to Menu
            }
        }

        // Add a short delay to reduce CPU usage (not strictly necessary in SFML)
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}


// #include "SDLNumberGrid.hpp"
// #include "Button.hpp"
// #include <SDL.h>
// #include <iostream>
// #include "Assets.hpp"
// using namespace std;

// int main(int argc, char* argv[]) {
//     Window window("2048 Game", 600, 900);
//     SDLNumberGrid grid(window);
//     GameObject gameOver = GameObject(window.getRenderer(), GAME_OVER, 75, 300, 450, 450);
//     GameObject gameWin = GameObject(window.getRenderer(), GAME_WIN, 75, 300, 450, 450);

//     GameObject background = GameObject(window.getRenderer(), GRID1, 75, 300, 450, 450);
//     Button undoButton = Button(window.getRenderer(), UNDO_BUTTON_NORMAL, UNDO_BUTTON_HOVER, UNDO_BUTTON_PRESSED, 365, 200, 50, 50, [&grid]() { grid.undo(); });
//     Button restartButton = Button(window.getRenderer(), RESTART_BUTTON_NORMAL, RESTART_BUTTON_HOVER, RESTART_BUTTON_PRESSED, 465, 200, 50, 50, [&grid]() { grid.reset(); });
//     GameObject scoreBoard = GameObject(window.getRenderer(), SCORE, 350, 100, 180, 80);

//     int fontSize1 = 60;
//     int fontSize2 = 20;
//     int fontSize3 = 40;
//     TTF_Font* font1 = TTF_OpenFont(FONT_PATH.c_str(), fontSize1);
//     TTF_Font* font2 = TTF_OpenFont(FONT_PATH.c_str(), fontSize2);
//     TTF_Font* font3 = TTF_OpenFont(FONT_PATH.c_str(), fontSize3);
//     if (!font1 || !font2 || !font3) {
//         std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
//         return 1;
//     }

//     bool quit = false;
//     SDL_Event event;
//     bool showGameWinScreen = false;

//     while (!quit) {
//         window.clear();
//         background.render(window.getRenderer());
//         undoButton.render(window.getRenderer());
//         restartButton.render(window.getRenderer());
//         scoreBoard.render(window.getRenderer());
//         grid.writeText("2048", font1, {113, 112, 107, 255}, 50, 100);
//         grid.writeText("SCORE", font2, {113, 112, 107, 255}, 405, 105);
//         grid.writeText(to_string(grid.getScore()), font3, {251, 248, 239, 255}, 405, 120);
//         grid.render();

//         if (grid.isGameOver() && !grid.canMove()) {
//             cout << "Game Over!" << endl;
//             cout << "Score: " << grid.getScore() << endl;
//             gameOver.render(window.getRenderer()); 
//             grid.writeText("GAME OVER!", font1, {113, 112, 107, 255}, 135, 480);
//         }

//         if (grid.isGameWon() && !showGameWinScreen) {
//             showGameWinScreen = true;
//             cout << "You won!" << endl;
//             cout << "Score: " << grid.getScore() << endl;
//         }

//         if (showGameWinScreen) {
//             gameWin.render(window.getRenderer()); 
//             grid.writeText("YOU WON!", font1, {113, 112, 107, 255}, 155, 450);
//             grid.writeText("Move to continue", font2, {113, 112, 107, 255}, 220, 530);
//         }

//         SDL_SetRenderDrawColor(window.getRenderer(), 251, 248, 239, 255);           
//         window.present();  

//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 quit = true;
//             } else if (event.type == SDL_KEYDOWN) {
//                 if (showGameWinScreen) {
//                     showGameWinScreen = false; 
//                 } else {
//                     grid.handleInput(event.key.keysym.sym);
//                 }
//             } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
//                 undoButton.handleEvent(&event);
//                 restartButton.handleEvent(&event);  
//             }
//         }

//         SDL_Delay(10);
//     }

//     TTF_CloseFont(font1);
//     TTF_CloseFont(font2);
//     TTF_CloseFont(font3);

//     return 0;
// }
