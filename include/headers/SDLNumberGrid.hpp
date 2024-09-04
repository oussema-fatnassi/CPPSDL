#ifndef SDLNUMBERGRID_HPP
#define SDLNUMBERGRID_HPP

#include "Window.hpp"
#include "GameObject.hpp"
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>


class SDLNumberGrid {
public:
    SDLNumberGrid(Window& window, int gridSize = 4, int tileSize = 100);
    ~SDLNumberGrid();

    void render();
    void handleInput(SDL_Keycode key);
    bool isGameOver() const;
    bool canMove() const;
    void writeText(const string& text, TTF_Font* font, SDL_Color color, int x, int y);
    int getScore() const;

private:
    bool addRandomNumber();                      // Add a random 2 or 4 to an empty cell
    bool isGridFull() const;                     // Check if the grid is full
    void moveLeft();                             // Move all numbers to the left
    void moveRight();                            // Move all numbers to the right
    void moveUp();                               // Move all numbers up
    void moveDown();                             // Move all numbers down
    void merge(std::vector<int>& row);           // Merge adjacent equal numbers

    Window& window;
    std::vector<std::vector<int>> grid;
    int gridSize;
    int tileSize;
    int xStart;
    int yStart;
    int offsetX;
    int offsetY;
    int score;

    TTF_Font* font;
    SDL_Color textColor;
    SDL_Color textColor2;
    
    void renderTile(int value, int x, int y);
};

#endif // SDLNUMBERGRID_HPP
