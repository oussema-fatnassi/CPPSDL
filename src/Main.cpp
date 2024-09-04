#include "SDLNumberGrid.hpp"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 900);
    GameObject background = GameObject(window.getRenderer(), "../assets/images/4x4_grid.svg", 75, 200, 450, 450);
    TTF_Font* font = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", 24);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    SDLNumberGrid grid(window);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        window.clear();
        background.render(window.getRenderer());
        grid.writeText("2048", font, {255, 255, 0, 255}, 460, 50);
        grid.render();
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

    TTF_CloseFont(font);

    return 0;
}
