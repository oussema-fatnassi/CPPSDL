#ifndef UI_HPP
#define UI_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include "Button.hpp"
#include "Text.hpp"
#include "GameObject.hpp"
#include <vector>
#include <string>
#include "Grid.hpp"
using namespace std;

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI();
    void addButton(Button* button);
    void addText(Text* text);
    void addGameObject(GameObject* gameObject);
    void render();
    void renderTile(int value, int x, int y);
    void renderGame();
    void clear();
    void setGrid(Grid* newGrid);
    void updateScoreText(const string& score);

private:
    SDL_Renderer* renderer;
    vector<Button*> buttons;
    vector<Text*> texts;
    vector<GameObject*> gameObjects;
    int gridSize;
    int tileSize;
    int xStart;
    int yStart;
    int offsetX;
    int offsetY;
    SDL_Color textColor;
    SDL_Color textColor2;
    TTF_Font* font;
    Grid* gridObject;
    vector<vector<int>> grid;

};

#endif // UI_HPP