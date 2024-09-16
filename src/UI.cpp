#include "UI.hpp"

UI::UI(SDL_Renderer* renderer)                                  // Constructor
    : renderer(renderer), font(nullptr), gridObject(nullptr), tileSize(100), xStart(75), yStart(300), offsetX(10), offsetY(8) {
    textColor = {255, 255, 255}; 
    textColor2 = {113, 112, 107};

    font = TTF_OpenFont(FONT_PATH.c_str(), 24);                 // Load the font for the UI
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }

    gridPropertiesMap[3] = {12, 135, 10, 10};                   // Set the grid properties for different grid sizes (gap, tileSize, offsetX, offsetY)  
    gridPropertiesMap[4] = {10, 100, 10, 8};   
    gridPropertiesMap[5] = {8, 80, 9, 9};   
    gridPropertiesMap[6] = {6, 68, 6, 6}; 
    gridPropertiesMap[8] = {3, 53, 2, 2}; 
}

UI::~UI() {                                                     // Destructor, delete all the UI elements
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

void UI::addButton(Button* button) {                            // Add button to the UI 
    buttons.push_back(button);
}

void UI::addText(Text* text) {                                  // Add text to the UI
    texts.push_back(text);
}

void UI::addGameObject(GameObject* gameObject) {                // Add game object to the UI
    gameObjects.push_back(gameObject);
}

void UI::addGameObjectEnd(GameObject* gameObjectEnd){           // Add game object for the end of game to the UI
    gameObjectsEnd.push_back(gameObjectEnd);
}

void UI::addTextEnd(Text* textEnd){                             // Add text for the end of game to the UI
    textsEnd.push_back(textEnd);
}

void UI::render() {                                             // Render the UI elements
    for (Button* button : buttons) {
        button->render(renderer);
    }

    for (GameObject* gameObject : gameObjects) {
        gameObject->render(renderer);
    }
    for (Text* text : texts) {
        if (text) { 
            text->render(renderer);
        }
    }

    renderGame();
    for (GameObject* gameObjectEnd : gameObjectsEnd) {
        gameObjectEnd->render(renderer);
    }

    for (Text* textEnd : textsEnd) {
        if (textEnd) { 
            textEnd->render(renderer);
        }
    }
}

void UI:: clear() {                                             // Clear the UI elements             
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

void UI::renderTile(int value, int x, int y) {                  // Render the tile with the value at the given position
    GameObject tile(renderer, value, x, y, tileSize, tileSize);
    tile.render(renderer);

    if (value != 0) {                                           // Render the value of the tile if it is not 0
        string text = to_string(value);
        SDL_Color color = (value <= 8) ? textColor2 : textColor;    // Set the color of the text based on the value
        
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            
            if (textTexture) {                                  // Render the text texture
                int textWidth, textHeight;
                SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

                SDL_Rect textRect = { x + (tileSize - textWidth) / 2, y + (tileSize - textHeight) / 2, textWidth, textHeight };

                if (SDL_RenderCopy(renderer, textTexture, nullptr, &textRect) != 0) {
                    std::cerr << "SDL_RenderCopy Error: " << SDL_GetError() << std::endl;
                }

                SDL_DestroyTexture(textTexture);
            } else {
                std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            }
        } else {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        }
    }
}

void UI::renderGame() {                                         // Render the game grid with the tiles
    if (gridObject == nullptr) {
        return; 
    }

    for (int i = 0; i < gridSize; i++) {                        // Render the tiles based on the grid size and the grid data
        for (int j = 0; j < gridSize; j++) {
            int x = xStart + j * (tileSize + TILE_GAP) + offsetX;
            int y = yStart + i * (tileSize + TILE_GAP) + offsetY;
            renderTile(grid[i][j], x, y);
        }
    }
}

void UI::setGrid(Grid* newGrid) {                               // Set the grid object in the UI
    gridObject = newGrid;
    gridSize = gridObject->getSize();
    grid = gridObject->getGridData();  

    auto it = gridPropertiesMap.find(gridSize);
    if (it != gridPropertiesMap.end()) {                        // Set the grid properties based on the grid size
        TILE_GAP = it->second.gap;
        tileSize = it->second.tileSize;
        offsetX = it->second.offsetX;
        offsetY = it->second.offsetY;
    } else {
        cerr << "Unsupported grid size: " << gridSize << endl;
    }
}
void UI::updateScoreText(const std::string& score) {            // Update the score text with the new score
    for (auto& text : texts) {
        if (text->getID() == 1111) {
            text->setText(score);
            break;
        }
    }
    renderGame();                                               // Re-render to update the UI
}

void UI::removeGameObject(GameObject* gameObject) {             // Remove the game object from the UI
    auto it = find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

void UI::removeText(Text* text) {                               // Remove the text from the UI
    auto it = find(texts.begin(), texts.end(), text);
    if (it != texts.end()) {
        texts.erase(it);
    }
}