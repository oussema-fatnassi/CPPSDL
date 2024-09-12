#include "UI.hpp"

UI::UI(sf::RenderWindow& window)                                            // Constructor
    : window(window), gridObject(nullptr), tileSize(100), xStart(75), yStart(300), offsetX(10), offsetY(8) {
    textColor = {255, 255, 255}; 
    textColor2 = {113, 112, 107};

    if (!loadFont(FONT_PATH)) {                                             // Load the font
        std::cerr << "Failed to load font!" << std::endl;
    }

    gridPropertiesMap[3] = {12, 135, 10, 10};                               // Set the grid properties for different grid sizes (gap, tileSize, offsetX, offsetY)  
    gridPropertiesMap[4] = {10, 100, 10, 8};   
    gridPropertiesMap[5] = {8, 80, 9, 9};   
    gridPropertiesMap[6] = {6, 68, 6, 6}; 
    gridPropertiesMap[8] = {3, 53, 2, 2}; 
}

UI::~UI() {                                                                 // Destructor, delete all the UI elements
    for (auto& button : buttons) {
        delete button;
    }
    for (auto& text : texts) {
        delete text;
    }
    for (auto& gameObject : gameObjects) {
        delete gameObject;
    }
    for(auto& gameObjectEnd : gameObjectsEnd){
        delete gameObjectEnd;
    }
    for(auto& textEnd : textsEnd){
        delete textEnd;
    }
}

void UI::addButton(Button* button) {                                        // Add button to the UI 
    buttons.push_back(button);
}

void UI::addText(Text* text) {                                              // Add text to the UI
    texts.push_back(text);
}

void UI::addGameObject(GameObject* gameObject) {                            // Add game object to the UI
    gameObjects.push_back(gameObject);
}

void UI::addGameObjectEnd(GameObject* gameObjectEnd){                       // Add game object for the end of game to the UI
    gameObjectsEnd.push_back(gameObjectEnd);
}

void UI::addTextEnd(Text* textEnd){                                         // Add text for the end of game to the UI
    textsEnd.push_back(textEnd);
}

void UI::render() {                                                         // Render the UI elements
    for (Button* button : buttons) {
        button->render();
    }

    for (GameObject* gameObject : gameObjects) {
        gameObject->render();
    }
    for (Text* text : texts) {
        if (text) { 
            text->render();
        }
    }

    renderGame();
    for (GameObject* gameObjectEnd : gameObjectsEnd) {
        gameObjectEnd->render();
    }

    for (Text* textEnd : textsEnd) {
        if (textEnd) { 
            textEnd->render();
        }
    }
}

void UI:: clear() {                                                         // Clear the UI elements             
    for (auto& button : buttons) {
        button = nullptr;
    }

    for (auto& text : texts) {
        text = nullptr;
    }

    for (auto& gameObject : gameObjects) {
        gameObject = nullptr;
    }

    for(auto& gameObjectEnd : gameObjectsEnd){
        gameObjectEnd = nullptr;
    }

    for(auto& textEnd : textsEnd){
        textEnd = nullptr;
    }

    buttons.clear();
    texts.clear();
    gameObjects.clear();
    gameObjectsEnd.clear();
    textsEnd.clear();
}

void UI::renderTile(int value, int x, int y) {                              // Render the tile based on the value, x, and y position
    GameObject tile(window, value, x, y, tileSize, tileSize);
    tile.render();  

    if (value != 0) {
        std::string textValue = std::to_string(value);                      // Render the value of the tile
        sf::Color color = (value <= 8) ? textColor2 : textColor;            // Set the text color based on the value    

        sf::Text tileText;
        tileText.setFont(font);                                             // Set the font
        tileText.setString(textValue);                                      // Set the text string to display the tile's value
        tileText.setFillColor(color);                                       // Set the text color

        unsigned int textSize;
        if (value <= 8192) {
            textSize = tileSize / 3;
        } else if (value <= 65536) {
            textSize = tileSize / 4;
        } else if (value <= 524288) {
            textSize = tileSize / 5;
        } else {
            textSize = tileSize / 6;
        }
        tileText.setCharacterSize(textSize);

        sf::FloatRect textBounds = tileText.getLocalBounds();               // Get the bounds of the text to center it      
        float textX = x + (tileSize - textBounds.width) / 2 - textBounds.left;
        float textY = y + (tileSize - textBounds.height) / 2 - textBounds.top;
        tileText.setPosition(textX, textY);

        window.draw(tileText);
    }
}

void UI::renderGame() {                                                     // Render the game grid with the tiles
    if (gridObject == nullptr) {
        return; 
    }

    for (int i = 0; i < gridSize; i++) {                                    // Render the tiles based on the grid size and the grid data
        for (int j = 0; j < gridSize; j++) {
            int x = xStart + j * (tileSize + TILE_GAP) + offsetX;
            int y = yStart + i * (tileSize + TILE_GAP) + offsetY;
            renderTile(grid[i][j], x, y);
        }
    }
}

void UI::setGrid(Grid* newGrid) {                                           // Set the grid object in the UI
    gridObject = newGrid;
    gridSize = gridObject->getSize();
    grid = gridObject->getGridData();  

    auto it = gridPropertiesMap.find(gridSize);
    if (it != gridPropertiesMap.end()) {                                    // Set the grid properties based on the grid size
        TILE_GAP = it->second.gap;
        tileSize = it->second.tileSize;
        offsetX = it->second.offsetX;
        offsetY = it->second.offsetY;

        cout << "Grid Size: " << gridSize << endl;
        for (const auto& row : grid) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    } else {
        cerr << "Unsupported grid size: " << gridSize << endl;
    }
}
void UI::updateScoreText(const std::string& score) {                        // Update the score text in the UI
    std::cout << "updateScoreText called with score: " << score << std::endl;
    for (auto& text : texts) {
        if (text->getID() == 2) {
            text->setText(score);
            std::cout << "Score: " << score << ", Text: " << text->getText() << std::endl;
            break;
        }
    }
    renderGame();
}

void UI::removeGameObject(GameObject* gameObject) {                         // Remove the game object from the UI
    auto it = find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

void UI::removeText(Text* text) {                                           // Remove the text from the UI
    auto it = find(texts.begin(), texts.end(), text);
    if (it != texts.end()) {
        texts.erase(it);
    }
}

bool UI::loadFont(const std::string& fontPath) {                            // Load the font from the file
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from file: " << fontPath << std::endl;
        return false;
    }
    return true;
}
