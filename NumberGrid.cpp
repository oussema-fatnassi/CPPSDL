#include "NumberGrid.hpp"
#include <iostream>
using namespace std;

NumberGrid::NumberGrid(int grid_size) : Grid(grid_size)
{
}

void NumberGrid::fillWith2048()
{
    cout << endl;
    int cellWidth = 4; 
    for (int i = 0; i <= 2 * getGridSize(); i++) {
        for (int j = 0; j <= getGridSize(); j++) {
            if (i % 2 == 0) {                                       // Horizontal lines
                if (j < getGridSize())
                    cout << " " << string(cellWidth , '-');         // Print centered horizontal line
            } else {                                                // Vertical lines and numbers
                if (j == 0)
                    cout << "|";                                    // Leading vertical line
                else {
                    cout.width(cellWidth);
                    cout << "    " << "|";                          // Print number and trailing vertical line
                }
            }
        }
        cout << endl;
    }
}
