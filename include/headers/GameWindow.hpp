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

    // Button shapes
    sf::RectangleShape resetButton, undoButton;

    // Textures for button states
    sf::Texture resetTexture, resetHoverTexture, resetPressedTexture;
    sf::Texture undoTexture, undoHoverTexture, undoPressedTexture;

    sf::RectangleShape scoreBox, highScoreBox; // Score and high score boxes

    int score;
    int highScore;

    void initializeUI();
    void updateUI();
    void drawUI();
    void drawGrid();

    // Helper functions for button state updates
    void updateButtonState(sf::RectangleShape& button, const sf::Texture& defaultTexture,
        const sf::Texture& hoverTexture, const sf::Texture& pressedTexture, bool& isPressed);

public:
    GameWindow(NumberGrid& grid, int windowSize);
    void run();
};

#endif // GAMEWINDOW_HPP
