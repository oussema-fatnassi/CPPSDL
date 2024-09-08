#ifndef SDLNUMBERGRID_HPP
#define SDLNUMBERGRID_HPP

#include "Window.hpp"
#include "GameObject.hpp"
#include <vector>
#include <algorithm>
#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
using namespace std;


class SDLNumberGrid {
public:
    SDLNumberGrid(Window& window, int gridSize = 4, int tileSize = 100);
    ~SDLNumberGrid();

    void render();
    void handleInput(SDL_Keycode key);
    bool isGameOver() const;
    bool isGameWon();
    bool canMove() const;
    void writeText(const string& text, TTF_Font* font, SDL_Color color, int x, int y);
    int getScore() const;
    void undo();
    void reset();
    bool gameWon = false;

private:
    bool addRandomNumber();                      // Add a random 2 or 4 to an empty cell
    bool isGridFull() const;                     // Check if the grid is full
    void moveLeft();                             // Move all numbers to the left
    void moveRight();                            // Move all numbers to the right
    void moveUp();                               // Move all numbers up
    void moveDown();                             // Move all numbers down
    void merge(vector<int>& row);           // Merge adjacent equal numbers
    bool gridHasChanged() const;                       // Check if the grid has changed
    void move(int dx, int dy);

    Window& window;
    vector<vector<int>> grid;
    int gridSize;
    int tileSize;
    int xStart;
    int yStart;
    int offsetX;
    int offsetY;
    int score;

    vector<vector<int>> previousGrid;
    int previousScore;
    bool canUndo;

    TTF_Font* font;
    SDL_Color textColor;
    SDL_Color textColor2;
    
    void renderTile(int value, int x, int y);
};

#endif // SDLNUMBERGRID_HPP
