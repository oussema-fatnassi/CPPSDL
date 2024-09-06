#ifndef NUMBERGRID_HPP
#define NUMBERGRID_HPP

#include "Grid.hpp"
#include "InputHandler.hpp"
#include <vector>
using namespace std;

class NumberGrid : public Grid
{
private:
    vector<vector<int>> grid;
    bool addRandomNumber();                                     // Add a random 2 or 4 to an empty cell
    bool isGridFull();                                          // Check if the grid is full

public:
    NumberGrid(int gridSize = 4);                               // Constructor
    void printGrid();                                           // Override to print the current grid state
    void move(InputHandler::Direction dir);                     // Simulate the user's move and add new number
    void moveLeft();                                            // Move all numbers to the left
    void moveRight();                                           // Move all numbers to the right
    void moveUp();                                              // Move all numbers up
    void moveDown();                                            // Move all numbers down
    void merge(vector<int>& row);     
    
public:
    const vector<vector<int>>& getGrid() const;
                          // Merge adjacent equal numbers
};

#endif // NUMBERGRID_HPP
