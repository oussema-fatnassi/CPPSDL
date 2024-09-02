#include "Grid.hpp"
#include <iostream>
using namespace std;

Grid::Grid(int grid_size) : gridSize(grid_size)
{
}

Grid::~Grid()
{
}

void Grid::printGrid()
{
    cout << endl;

    for (int i = 0; i <= 2 * gridSize; i++) {
        for (int j = 0; j <= 2 * gridSize; j++) {
            if (i % 2 == 0) {                       // Horizontal lines
                if (j % 2 == 0)
                    cout << " ";                    // Space between horizontal lines
                else
                    cout << "---";                  // Horizontal line segment
            } else {                                // Vertical lines and spaces
                if (j % 2 == 0)
                    cout << "|";                    // Vertical line
                else
                    cout << "   ";                  // Space between vertical lines
            }
        }
        cout << endl;
    }
}