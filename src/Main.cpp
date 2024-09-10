#include "GameWindow.hpp"
#include "NumberGrid.hpp"

int main() {
    NumberGrid numberGrid(4);  // Create a 4x4 grid
    GameWindow gameWindow(numberGrid, 600); // Pass grid and window size
    gameWindow.run();
    return 0;
}
