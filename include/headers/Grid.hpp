#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <../sdl/SDL.h>
using namespace std;

class Grid {
public: 
    Grid(int size);
    ~Grid();

    void handleInput(SDL_Keycode key);
    bool isGameOver() const;
    bool isGameWon();
    bool canMove() const;
    int getScore() const;
    void undo();
    void reset();
    bool gameWon = false;

private:
    bool addRandomNumber();                      // Add a random 2 or 4 to an empty cell
    bool isGridFull() const;                     // Check if the grid is full
    void merge(vector<int>& row);           // Merge adjacent equal numbers
    bool gridHasChanged() const;                       // Check if the grid has changed
    void move(int dx, int dy);

    vector<vector<int>> grid;
    int gridSize;
    int score;

    vector<vector<int>> previousGrid;
    int previousScore;
    bool canUndo;
};


#endif // GRID_HPP