#include <iostream>
#include "Window.hpp"
#include "GameObject.hpp"

int main() {
    Window window("Testing", 600, 900);

    GameObject gameObject(window.getRenderer(), 8, 85, 210, 100, 100);

    while (!window.isClosed()) {
        window.pollEvents();
        window.clear();

        window.renderImage("../assets/images/4x4_grid.svg", 75, 200, 450, 450);
        
        gameObject.render(window.getRenderer());

        window.present();
        SDL_Delay(10);
    }

    return 0;
}
