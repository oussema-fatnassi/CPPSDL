#include "GameWindow.hpp"
#include <SFML/Window/Event.hpp>
#include <sstream>

GameWindow::GameWindow(NumberGrid& grid, int windowSize)
    : window(sf::VideoMode(windowSize, windowSize + 100), "2048 Game"), grid(grid), score(0), highScore(0) {
    if (!font.loadFromFile("C:/Users/admin/Desktop/Tile Twister/CPPSDL/ClearSansBold.ttf")) { // Ensure you have a valid font path
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
    titleText.setPosition(10, 20);

    // Score Label
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color(119, 110, 101));
    scoreLabel.setPosition(300, 10);

    // Score display setup
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(300, 40);

    // High Score Label
    highScoreLabel.setFont(font);
    highScoreLabel.setString("HIGH SCORE");
    highScoreLabel.setCharacterSize(18);
    highScoreLabel.setFillColor(sf::Color(119, 110, 101));
    highScoreLabel.setPosition(450, 10);

    // High Score display setup
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(500, 40);

    // Reset button setup
    resetButton.setSize(sf::Vector2f(50, 20));
    resetButton.setFillColor(sf::Color(142, 121, 97));
    resetButton.setPosition(300, 80);

    // Undo button setup
    undoButton.setSize(sf::Vector2f(50, 20));
    undoButton.setFillColor(sf::Color(142, 121, 97));
    undoButton.setPosition(500, 80);
}

void GameWindow::updateUI() {
    // Update score text
    std::stringstream ss;
    ss << grid.getScore(); // Access score from NumberGrid
    scoreText.setString(ss.str());

    // Update high score if the current score is greater
    highScore = std::max(highScore, grid.getScore());

    std::stringstream ssHigh;
    ssHigh << highScore;
    highScoreText.setString(ssHigh.str());
}



void GameWindow::drawUI() {
    window.draw(titleText);
    window.draw(scoreLabel);
    window.draw(scoreText);
    window.draw(highScoreLabel);
    window.draw(highScoreText);
    window.draw(resetButton);
    window.draw(undoButton);
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

            // Use the public getGrid() function to access the grid
            int value = grid.getGrid()[i][j];
            switch (value) {
                case 2: tile.setFillColor(sf::Color(238, 228, 218)); break;
                case 4: tile.setFillColor(sf::Color(237, 224, 200)); break;
                case 8: tile.setFillColor(sf::Color(242, 177, 121)); break;
                case 16: tile.setFillColor(sf::Color(245, 149, 99)); break;
                case 32: tile.setFillColor(sf::Color(246, 124, 95)); break;
                case 64: tile.setFillColor(sf::Color(246, 94, 59)); break;
                default: tile.setFillColor(sf::Color(205, 193, 180)); break;
            }

            window.draw(tile);

            if (value != 0) {
                sf::Text numberText;
                numberText.setFont(font);
                numberText.setString(std::to_string(value));
                numberText.setCharacterSize(32);
                numberText.setFillColor(sf::Color(119, 110, 101));
                numberText.setPosition(tile.getPosition().x + tileSize / 2 - numberText.getGlobalBounds().width / 2,
                                    tile.getPosition().y + tileSize / 2 - numberText.getGlobalBounds().height / 2);
                window.draw(numberText);
            }
        }
    }
}

void GameWindow::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        grid.move(InputHandler::Direction::LEFT); // Handle left move
                        break;
                    case sf::Keyboard::Right:
                        grid.move(InputHandler::Direction::RIGHT); // Handle right move
                        break;
                    case sf::Keyboard::Up:
                        grid.move(InputHandler::Direction::UP); // Handle up move
                        break;
                    case sf::Keyboard::Down:
                        grid.move(InputHandler::Direction::DOWN); // Handle down move
                        break;
                    default:
                        break;
                }
                updateUI(); // Update the score and high score display
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (resetButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    // Handle reset: Clear the grid and reset the score
                    grid = NumberGrid(4); // Reinitialize the grid
                    score = 0;
                    highScore = std::max(highScore, score);
                    updateUI();
                }
                if (undoButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    // Handle undo logic if implemented
                }
            }
        }

        window.clear(sf::Color(250, 248, 239)); // Background color to match the game style
        drawUI();
        drawGrid(); // Draw the grid and tiles
        window.display();
    }
}
