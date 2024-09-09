#include "Button.hpp"
#include <iostream>
#include "Menu.hpp"
#include "Window.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 900);
    UI ui(window.getRenderer());
    Menu menu(window.getRenderer());

    bool quit = false;
    SDL_Event event;

    menu.drawMainMenu();

    while (!quit) {
        window.clear();
        menu.update();


        SDL_SetRenderDrawColor(window.getRenderer(), 251, 248, 239, 255);           
        window.present();  

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                menu.handleEvent(&event);
            } else if (event.type == SDL_KEYDOWN) {
                menu.handleInput(event.key.keysym.sym);  // Pass key events to the Menu
            }
        }

        SDL_Delay(10);
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

//     GameObject background = GameObject(window.getRenderer(), GRID, 75, 300, 450, 450);
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
