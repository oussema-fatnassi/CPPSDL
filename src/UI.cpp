#include "UI.hpp"
#include <iostream>
#include "Assets.hpp"
using namespace std;
#include "vector"

UI::UI(SDL_Renderer* renderer) 
    : renderer(renderer), font(nullptr), gridObject(nullptr), tileSize(100), xStart(75), yStart(300), offsetX(10), offsetY(8) {
    textColor = {255, 255, 255}; 
    textColor2 = {113, 112, 107};

    font = TTF_OpenFont(FONT_PATH.c_str(), 24); // Adjust path and size
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }

    gridPropertiesMap[3] = {12, 135, 10, 10};  
    gridPropertiesMap[4] = {10, 100, 10, 8};   
    gridPropertiesMap[5] = {8, 80, 9, 9};   
    gridPropertiesMap[6] = {6, 68, 6, 6}; 
    gridPropertiesMap[8] = {3, 53, 2, 2}; 
}

UI::~UI() {
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

void UI::addButton(Button* button) {
    buttons.push_back(button);
}

void UI::addText(Text* text) {
    texts.push_back(text);
}

void UI::addGameObject(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
}

void UI::addGameObjectEnd(GameObject* gameObjectEnd){
    gameObjectsEnd.push_back(gameObjectEnd);
}

void UI::addTextEnd(Text* textEnd){
    textsEnd.push_back(textEnd);
}

void UI::render() {
    for (Button* button : buttons) {
        button->render(renderer);
    }


    for (GameObject* gameObject : gameObjects) {
        gameObject->render(renderer);
    }
    for (Text* text : texts) {
        if (text) { // Ensure text is not null
            text->render(renderer);
        }
    }

    renderGame();
    for (GameObject* gameObjectEnd : gameObjectsEnd) {
        gameObjectEnd->render(renderer);
    }

    for (Text* textEnd : textsEnd) {
        if (textEnd) { // Ensure text is not null
            textEnd->render(renderer);
        }
    }
}

void UI:: clear() {
    for (auto& button : buttons) {
        button->disable();
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

void UI::renderTile(int value, int x, int y) {
    GameObject tile(renderer, value, x, y, tileSize, tileSize);
    tile.render(renderer);

    if (value != 0) {
        string text = to_string(value);
        SDL_Color color = (value <= 8) ? textColor2 : textColor;
        
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
            
            if (textTexture) {
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


const int TILE_GAP = 10;

void UI::renderGame() {
    if (gridObject == nullptr) {
        return; 
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int x = xStart + j * (tileSize + TILE_GAP) + offsetX;
            int y = yStart + i * (tileSize + TILE_GAP) + offsetY;
            renderTile(grid[i][j], x, y);
        }
    }
}

void UI::setGrid(Grid* newGrid) {
    gridObject = newGrid;
    gridSize = gridObject->getSize();
    grid = gridObject->getGridData();  

    auto it = gridPropertiesMap.find(gridSize);
    if (it != gridPropertiesMap.end()) {
        TILE_GAP = it->second.gap;
        tileSize = it->second.tileSize;
        offsetX = it->second.offsetX;
        offsetY = it->second.offsetY;

        // Debugging output
        cout << "Grid Size: " << gridSize << endl;
        for (const auto& row : grid) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    } else {
        cerr << "Unsupported grid size: " << gridSize << endl;
        // Set default properties or handle error
    }
}
void UI::updateScoreText(const std::string& score) {
    // Update the score text with the new score
    for (auto& text : texts) {
        if (text->getID() == 1111) {
            text->setText(score);
            break;
        }
    }
    renderGame(); // Re-render to update the UI
}

void UI::removeGameObject(GameObject* gameObject) {
    auto it = find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObjects.erase(it);
    }
}

void UI::removeText(Text* text) {
    auto it = find(texts.begin(), texts.end(), text);
    if (it != texts.end()) {
        texts.erase(it);
    }
}