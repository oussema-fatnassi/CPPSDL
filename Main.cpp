#include "GameWindow.hpp"
#include "NumberGrid.hpp"

int main() {
    NumberGrid numberGrid(4);
    GameWindow gameWindow(numberGrid, 600); // 600x600 window size

    gameWindow.run();

    return 0;
}
