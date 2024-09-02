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
    bool addRandomNumber();  // Add a random 2 or 4 to an empty cell
    bool isGridFull();       // Check if the grid is full

public:
    NumberGrid(int gridSize = 4);  
    void printGrid();        // Override to print the current grid state
    void move(InputHandler::Direction dir);             // Simulate the user's move and add new number
};

#endif // NUMBERGRID_HPP
