#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include "Assets.hpp"
#include "Button.hpp"
#include "GameObject.hpp"
#include "Grid.hpp"
#include "Text.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct GridProperties {   // GridProperties struct used for storing grid properties
    int gap;
    int tileSize;
    int offsetX;
    int offsetY;
};

class UI {  // UI class used for creating the user interface and managing all the rendering
public:
    UI(sf::RenderWindow& window);  // Constructor
    ~UI();  // Destructor

    void addButton(Button* button);  // Public methods
    void addText(Text* text);
    void addGameObject(GameObject* gameObject);
    void addTextEnd(Text* text);
    void addGameObjectEnd(GameObject* gameObject);
    void render();
    void renderTile(int value, int x, int y);
    void renderGame();
    void clear();
    void updateScoreText(const std::string& score);
    void removeGameObject(GameObject* gameObject);
    void removeText(Text* text);
    void setGrid(Grid* newGrid);  // Setters

private:
    sf::RenderWindow& window;  // Reference to the SFML window
    std::vector<Button*> buttons;
    std::vector<Text*> texts, textsEnd;
    std::vector<GameObject*> gameObjects, gameObjectsEnd;
    int gridSize, tileSize, xStart, yStart, offsetX, offsetY, TILE_GAP;
    sf::Color textColor, textColor2;
    sf::Font font;  // SFML font for text rendering
    Grid* gridObject;
    std::vector<std::vector<int>> grid;
    std::unordered_map<int, GridProperties> gridPropertiesMap;

    bool loadFont(const std::string& fontPath);  // Helper method for loading fonts
};

#endif // UI_HPP
