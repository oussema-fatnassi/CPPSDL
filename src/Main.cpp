#include "SDLNumberGrid.hpp"
#include "Button.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 900);
    SDLNumberGrid grid(window);
    GameObject gameOver = GameObject(window.getRenderer(), "../assets/images/game_over.svg", 75, 300, 450, 450);
    GameObject gameWin = GameObject(window.getRenderer(), "../assets/images/game_win.svg", 75, 300, 450, 450);

    GameObject background = GameObject(window.getRenderer(), "../assets/images/4x4_grid.svg", 75, 300, 450, 450);
    Button undoButton = Button(window.getRenderer(), "../assets/images/undo.svg", "../assets/images/undo_hover.svg", "../assets/images/undo_pressed.svg", 365, 200, 50, 50, [&grid]() { grid.undo(); });
    Button restartButton = Button(window.getRenderer(), "../assets/images/restart.svg", "../assets/images/restart_hover.svg", "../assets/images/restart_pressed.svg", 465, 200, 50, 50, [&grid]() { grid.reset(); });
    GameObject scoreBoard = GameObject(window.getRenderer(), "../assets/images/score.svg", 350, 100, 180, 80);

    int fontSize1 = 60;
    int fontSize2 = 20;
    int fontSize3 = 40;
    TTF_Font* font1 = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize1);
    TTF_Font* font2 = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize2);
    TTF_Font* font3 = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize3);
    if (!font1 || !font2 || !font3) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event event;
    bool showGameWinScreen = false;

    while (!quit) {
        window.clear();
        background.render(window.getRenderer());
        undoButton.render(window.getRenderer());
        restartButton.render(window.getRenderer());
        scoreBoard.render(window.getRenderer());
        grid.writeText("2048", font1, {113, 112, 107, 255}, 50, 100);
        grid.writeText("SCORE", font2, {113, 112, 107, 255}, 405, 105);
        grid.writeText(to_string(grid.getScore()), font3, {251, 248, 239, 255}, 405, 120);
        grid.render();

        if (grid.isGameOver() && !grid.canMove()) {
            cout << "Game Over!" << endl;
            cout << "Score: " << grid.getScore() << endl;
            gameOver.render(window.getRenderer()); 
            grid.writeText("GAME OVER!", font1, {113, 112, 107, 255}, 135, 480);
        }

        if (grid.isGameWon() && !showGameWinScreen) {
            showGameWinScreen = true;
            cout << "You won!" << endl;
            cout << "Score: " << grid.getScore() << endl;
        }

        if (showGameWinScreen) {
            gameWin.render(window.getRenderer()); 
            grid.writeText("YOU WON!", font1, {113, 112, 107, 255}, 155, 450);
            grid.writeText("Move to continue", font2, {113, 112, 107, 255}, 220, 530);
        }

        SDL_SetRenderDrawColor(window.getRenderer(), 251, 248, 239, 255);           
        window.present();  

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (showGameWinScreen) {
                    showGameWinScreen = false; 
                } else {
                    grid.handleInput(event.key.keysym.sym);
                }
            } else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                undoButton.handleEvent(&event);
                restartButton.handleEvent(&event);  
            }
        }

        SDL_Delay(10);
    }

    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);

    return 0;
}
