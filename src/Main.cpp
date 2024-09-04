#include "SDLNumberGrid.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 900);
    GameObject background = GameObject(window.getRenderer(), "../assets/images/4x4_grid.svg", 75, 300, 450, 450);
    GameObject undoButton = GameObject(window.getRenderer(), "../assets/images/undo.svg", 365, 200, 50, 50);
    GameObject restartButton = GameObject(window.getRenderer(), "../assets/images/restart.svg", 465, 200, 50, 50);
    GameObject scoreBoard = GameObject(window.getRenderer(), "../assets/images/score.svg", 350, 100, 180, 80);
    int fontSize1 = 60;
    int fontSize2 = 20;
    int fontSize3 = 40;
    TTF_Font* font1 = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize1);
    TTF_Font* font2= TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize2);
    TTF_Font* font3 = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", fontSize3);
    if (!font1 || !font2 || !font3 ) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDLNumberGrid grid(window);

    bool quit = false;
    SDL_Event event;

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
        SDL_SetRenderDrawColor(window.getRenderer(), 251, 248, 239, 255);           // Set color background
        window.present();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                grid.handleInput(event.key.keysym.sym);
            }
        }

        if (grid.isGameOver() && !grid.canMove()) {
            quit = true;
        }

        SDL_Delay(100);
    }

    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);

    return 0;
}
