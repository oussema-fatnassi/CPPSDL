#ifndef NUMBERGRID_HPP
#define NUMBERGRID_HPP

#include "Grid.hpp"
#include "InputHandler.hpp"
#include <vector>
#include <stack> // Add stack for storing previous states

using namespace std;

class NumberGrid : public Grid {
private:
    vector<vector<int>> grid;
    int score;
    stack<pair<vector<vector<int>>, int>> previousStates; // Stack to save previous states of the grid and score

    bool addRandomNumber(); // Add a random 2 or 4 to an empty cell
    bool isGridFull(); // Check if the grid is full

public:
    NumberGrid(int gridSize = 4);
    void printGrid();
    void move(InputHandler::Direction dir);
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    void merge(vector<int>& row);

    void saveState();             // Save current state
    void restoreState();          // Restore previous state

    int getScore() const { return score; }
    const vector<vector<int>>& getGrid() const;
};

#endif // NUMBERGRID_HPP
