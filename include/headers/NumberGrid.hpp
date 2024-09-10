#ifndef NUMBERGRID_HPP
#define NUMBERGRID_HPP

#include "Grid.hpp"
#include "InputHandler.hpp"
#include <vector>

using namespace std;

class NumberGrid : public Grid {
private:
    vector<vector<int>> grid;
    int score; // Add score member variable
    bool addRandomNumber(); // Add a random 2 or 4 to an empty cell
    bool isGridFull(); // Check if the grid is full

public:
    NumberGrid(int gridSize = 4); // Constructor
    void printGrid(); // Override to print the current grid state
    void move(InputHandler::Direction dir); // Simulate the user's move and add new number
    bool moveLeft(); // Move all numbers to the left
    bool moveRight(); // Move all numbers to the right
    bool moveUp(); // Move all numbers up
    bool moveDown(); // Move all numbers down
    void merge(vector<int>& row); // Merge adjacent equal numbers

    // Getter for the score and the grid
    int getScore() const { return score; }
    const vector<vector<int>>& getGrid() const; // Correct declaration of getGrid()
};

#endif // NUMBERGRID_HPP
