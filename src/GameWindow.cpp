#include "GameWindow.hpp"
#include <iostream>

GameWindow::GameWindow(NumberGrid& grid, int windowSize)
    : window(sf::VideoMode(windowSize, windowSize), "2048"),
      numberGrid(grid),
      windowSize(windowSize),
      cellSize(windowSize / grid.getGridSize()) 
{
    // Color mapping for different numbers
    colorMap[0] = sf::Color(205, 193, 180);
    colorMap[2] = sf::Color(238, 228, 218);
    colorMap[4] = sf::Color(237, 224, 200);
    colorMap[8] = sf::Color(242, 177, 121);
    colorMap[16] = sf::Color(245, 149, 99);
    colorMap[32] = sf::Color(246, 124, 95);
    colorMap[64] = sf::Color(246, 94, 59);
    colorMap[128] = sf::Color(237, 207, 114);
    colorMap[256] = sf::Color(237, 204, 97);
    colorMap[512] = sf::Color(237, 200, 80);
    colorMap[1024] = sf::Color(237, 197, 63);
    colorMap[2048] = sf::Color(237, 194, 46);
}

void GameWindow::run() {
    while (window.isOpen()) {
        handleInput();
        window.clear(sf::Color::White);
        drawGrid();
        window.display();
    }
}

void GameWindow::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed) {
            InputHandler::Direction dir = InputHandler::Direction::NONE;
            if (event.key.code == sf::Keyboard::Up) dir = InputHandler::Direction::UP;
            if (event.key.code == sf::Keyboard::Down) dir = InputHandler::Direction::DOWN;
            if (event.key.code == sf::Keyboard::Left) dir = InputHandler::Direction::LEFT;
            if (event.key.code == sf::Keyboard::Right) dir = InputHandler::Direction::RIGHT;

            if (dir != InputHandler::Direction::NONE) {
                numberGrid.move(dir);
            }
        }
    }
}

void GameWindow::drawGrid() {
    int gridSize = numberGrid.getGridSize();
    const auto& grid = numberGrid.getGrid();

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor(getColor(grid[i][j]));

            window.draw(cell);

            if (grid[i][j] != 0) {
                sf::Text text;
                sf::Font font;
                if (!font.loadFromFile("arial.ttf")) {
                    std::cerr << "Failed to load font" << std::endl;
                    return;
                }

                text.setFont(font);
                text.setString(std::to_string(grid[i][j]));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Black);

                // Center the text in the cell
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                text.setPosition(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2);

                window.draw(text);
            }
        }
    }
}

sf::Color GameWindow::getColor(int value) {
    if (colorMap.find(value) != colorMap.end()) {
        return colorMap[value];
    } else {
        return sf::Color::Black; // Default color for unknown values
    }
}

