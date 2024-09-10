#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "NumberGrid.hpp"

class GameWindow {
private:
    sf::RenderWindow window;
    NumberGrid grid;
    sf::Font font;
    sf::Text titleText, scoreText, highScoreText, scoreLabel, highScoreLabel;
    sf::RectangleShape resetButton, undoButton;

    int score;
    int highScore;

    void initializeUI();
    void updateUI();
    void drawUI();
    void drawGrid(); // Declare the drawGrid function here

public:
    GameWindow(NumberGrid& grid, int windowSize);
    void run();
};

#endif // GAMEWINDOW_HPP
