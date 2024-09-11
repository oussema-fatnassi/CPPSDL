#include "GameWindow.hpp"
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iostream> // Include this header to use std::cerr

GameWindow::GameWindow(NumberGrid& grid, int windowSize)
    : window(sf::VideoMode(windowSize, windowSize + 100), "2048 Game"), grid(grid), score(0), highScore(0) {
    if (!font.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/fonts/ClearSansBold.ttf")) { // Ensure you have a valid font path
        // Handle error
    }

    initializeUI();
}

void GameWindow::initializeUI() {
    // Game Title Setup
    titleText.setFont(font);
    titleText.setString("2048");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color(119, 110, 101));
    titleText.setPosition(60, 20);

    // Score Label
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color(119, 110, 101));
    scoreLabel.setPosition(360, 10);

    // Score Box
    scoreBox.setSize(sf::Vector2f(80, 40));
    scoreBox.setFillColor(sf::Color(187, 173, 160));
    scoreBox.setPosition(360, 30);

    // Score display setup
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(360, 35);

    // High Score Label
    highScoreLabel.setFont(font);
    highScoreLabel.setString("HIGH SCORE");
    highScoreLabel.setCharacterSize(18);
    highScoreLabel.setFillColor(sf::Color(119, 110, 101));
    highScoreLabel.setPosition(450, 10);

    // High Score Box
    highScoreBox.setSize(sf::Vector2f(100, 40));
    highScoreBox.setFillColor(sf::Color(187, 173, 160));
    highScoreBox.setPosition(450, 30);

    // High Score display setup
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(460, 35);

    // Load textures for the reset button states
    if (!resetTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/restart.png")) {
    }
    if (!resetHoverTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/restart_hover.png")) {
    }
    if (!resetPressedTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/restart_pressed.png")) {
    }
    // Load textures for the undo button states
    if (!undoTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/undo.png")) { 
    }
    if (!undoHoverTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/undo_hover.png")) { 
    }
    if (!undoPressedTexture.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/assets/images/undo_pressed.png")) {
    }

    // Reset button setup
    resetButton.setSize(sf::Vector2f(50, 50));
    resetButton.setTexture(&resetTexture); // Set the default texture
    resetButton.setPosition(450, 90);

    // Undo button setup
    undoButton.setSize(sf::Vector2f(50, 50));
    undoButton.setTexture(&undoTexture); // Set the default texture
    undoButton.setPosition(370, 90);
}

void GameWindow::updateUI() {
    // Update score text
    std::stringstream ss;
    ss << grid.getScore();
    scoreText.setString(ss.str());

    // Update high score if the current score is greater
    highScore = std::max(highScore, grid.getScore());

    std::stringstream ssHigh;
    ssHigh << highScore;
    highScoreText.setString(ssHigh.str());
}

void GameWindow::drawUI() {
    window.draw(titleText);
    window.draw(scoreBox);
    window.draw(scoreLabel);
    window.draw(scoreText);
    window.draw(highScoreBox);
    window.draw(highScoreLabel);
    window.draw(highScoreText);
    window.draw(resetButton);
    window.draw(undoButton);
}

void GameWindow::updateButtonState(sf::RectangleShape& button, const sf::Texture& defaultTexture,
    const sf::Texture& hoverTexture, const sf::Texture& pressedTexture, bool& isPressed) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            button.setTexture(&pressedTexture);
            isPressed = true;
        } else {
            button.setTexture(&hoverTexture);
            if (isPressed) {
                isPressed = false;
            }
        }
    } else {
        button.setTexture(&defaultTexture);
    }
}

void GameWindow::run() {
    bool resetPressed = false, undoPressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        grid.move(InputHandler::Direction::LEFT);
                        break;
                    case sf::Keyboard::Right:
                        grid.move(InputHandler::Direction::RIGHT);
                        break;
                    case sf::Keyboard::Up:
                        grid.move(InputHandler::Direction::UP);
                        break;
                    case sf::Keyboard::Down:
                        grid.move(InputHandler::Direction::DOWN);
                        break;
                    default:
                        break;
                }
                updateUI();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (resetButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    grid = NumberGrid(4);
                    score = 0;
                    highScore = std::max(highScore, score);
                    updateUI();
                }
                if (undoButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    // Restore the previous state of the game
                    grid.restoreState();
                    updateUI();
                }
            }
        }

        updateButtonState(resetButton, resetTexture, resetHoverTexture, resetPressedTexture, resetPressed);
        updateButtonState(undoButton, undoTexture, undoHoverTexture, undoPressedTexture, undoPressed);

        window.clear(sf::Color(250, 248, 239)); 
        drawUI();
        drawGrid(); 
        window.display();
    }
}


void GameWindow::drawGrid() {
    const int gridSize = 4; // 4x4 grid
    const float tileSize = 100.f;
    const float tileSpacing = 4.f;
    sf::Vector2f gridStartPosition(100, 170); // Adjust starting position

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(gridStartPosition.x + j * (tileSize + tileSpacing),
                             gridStartPosition.y + i * (tileSize + tileSpacing));

            int value = grid.getGrid()[i][j];
            switch (value) {
                case 2: 
                    tile.setFillColor(sf::Color(238, 228, 218)); break;
                case 4: 
                    tile.setFillColor(sf::Color(237, 224, 200)); break;
                case 8: 
                    tile.setFillColor(sf::Color(242, 177, 121)); break;
                case 16: 
                    tile.setFillColor(sf::Color(245, 149, 99)); break;
                case 32: 
                    tile.setFillColor(sf::Color(246, 124, 95)); break;
                case 64: 
                    tile.setFillColor(sf::Color(246, 94, 59)); break;
                case 128: 
                    tile.setFillColor(sf::Color(237, 207, 114)); break;
                case 256: 
                    tile.setFillColor(sf::Color(237, 204, 97)); break;
                case 512: 
                    tile.setFillColor(sf::Color(237, 200, 80)); break;
                case 1024: 
                    tile.setFillColor(sf::Color(237, 197, 63)); break;
                case 2048: 
                    tile.setFillColor(sf::Color(237, 194, 46)); break;
                default: 
                    tile.setFillColor(sf::Color(205, 193, 180)); break;
            }

            window.draw(tile);

            // Draw the number if the tile value is not zero
            if (value != 0) {
                sf::Text numberText;
                numberText.setFont(font);
                numberText.setString(std::to_string(value));
                numberText.setCharacterSize(32);
                numberText.setFillColor(sf::Color(119, 110, 101)); // Text color
                numberText.setPosition(
                    tile.getPosition().x + tileSize / 2 - numberText.getGlobalBounds().width / 2,
                    tile.getPosition().y + tileSize / 2 - numberText.getGlobalBounds().height / 2
                );
                window.draw(numberText);
            }
        }
    }
}
