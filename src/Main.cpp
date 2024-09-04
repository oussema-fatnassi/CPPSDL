#include <iostream>
#include "Window.hpp"
#include "GameObject.hpp"

int main() {
    Window window("Testing", 600, 900);

    int x = 75;
    int y = 200;
    int width = 450;
    int height = 450;
    GameObject gameObject(8, x, y, 100, 100);

    while (!window.isClosed()) {
        window.pollEvents();
        window.clear();

        window.renderImage("../assets/images/4x4_grid.svg", x, y, width, height);
        window.renderGameObject(&gameObject);

        SDL_Delay(10); 
    }

    return 0;
}
