#include "SDLNumberGrid.hpp"
#include <../sdl/SDL.h>
#include <../sdl/SDL_image.h>

int main(int argc, char* argv[]) {
    Window window("2048 Game", 600, 600);

    SDLNumberGrid grid(window);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                grid.handleInput(event.key.keysym.sym);
            }
        }

        grid.render();

        if (grid.isGameOver()) {
            quit = true;
        }

        SDL_Delay(100);
    }

    return 0;
}