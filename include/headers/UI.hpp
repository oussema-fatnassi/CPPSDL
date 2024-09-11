#ifndef UI_HPP
#define UI_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include "Assets.hpp"
#include "Button.hpp"
#include "GameObject.hpp"
#include "Grid.hpp"
#include "Text.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct GridProperties {                                     // GridProperties struct used for storing grid properties
    int gap;
    int tileSize;
    int offsetX;
    int offsetY;
};

class UI {                                                  // UI class used for creating the user interface and managind all the rendering
public:
    UI(SDL_Renderer* renderer);                             // Constructor   
    ~UI();                                                  // Destructor         

    void addButton(Button* button);                         // Public methods
    void addText(Text* text);
    void addGameObject(GameObject* gameObject);
    void addTextEnd(Text* text);
    void addGameObjectEnd(GameObject* gameObject);
    void render();
    void renderTile(int value, int x, int y);
    void renderGame();
    void clear();
    void updateScoreText(const string& score);
    void removeGameObject(GameObject* gameObject);
    void removeText(Text* text);
    void setGrid(Grid* newGrid);                            // Setters  

private:
    SDL_Renderer* renderer;                                 // Member variables
    vector<Button*> buttons;
    vector<Text*> texts, textsEnd;
    vector<GameObject*> gameObjects, gameObjectsEnd;
    int gridSize, tileSize, xStart, yStart, offsetX, offsetY, TILE_GAP;
    SDL_Color textColor, textColor2;
    TTF_Font* font;
    Grid* gridObject;
    vector<vector<int>> grid;
    unordered_map<int, GridProperties> gridPropertiesMap;
};

#endif // UI_HPP
