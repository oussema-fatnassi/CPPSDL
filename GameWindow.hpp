#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "NumberGrid.hpp"

class GameWindow {
private:
    sf::RenderWindow window;
    NumberGrid& numberGrid;
    int windowSize;
    int cellSize;
    std::map<int, sf::Color> colorMap;

public:
    GameWindow(NumberGrid& grid, int windowSize);
    void run();
    void drawGrid();
    void handleInput();
    sf::Color getColor(int value);
};

#endif // GAMEWINDOW_HPP
