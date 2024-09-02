#include "NumberGrid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

NumberGrid::NumberGrid(int gridSize) : Grid(gridSize), grid(gridSize, vector<int>(gridSize, 0))
{
    srand(time(0));  // Seed for random number generation
    addRandomNumber();  // Start by adding a random 2 or 4
    addRandomNumber();  // Add a second random number
}

bool NumberGrid::addRandomNumber()
{
    vector<pair<int, int>> emptyCells;

    // Find all empty cells
    for (int i = 0; i < getGridSize(); i++) {
        for (int j = 0; j < getGridSize(); j++) {
            if (grid[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    if (emptyCells.empty()) {
        return false;
    }

    // Select a random empty cell
    int randIndex = rand() % emptyCells.size();
    int randValue = (rand() % 2 + 1) * 2;  // Randomly pick 2 or 4

    grid[emptyCells[randIndex].first][emptyCells[randIndex].second] = randValue;

    return true;
}

bool NumberGrid::isGridFull()
{
    for (int i = 0; i < getGridSize(); i++) {
        for (int j = 0; j < getGridSize(); j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void NumberGrid::printGrid()
{
    int cellWidth = 5;

    cout << endl;
    for (int i = 0; i < getGridSize(); i++) {
        cout << " ";
        for (int j = 0; j < getGridSize(); j++) {
            cout << string(cellWidth, '-');  // Print horizontal lines
            if (j < getGridSize() - 1)
                cout << "-"; // Add an extra dash between cells
        }
        cout << endl;
        for (int j = 0; j < getGridSize(); j++) {
            cout << "|";
            if (grid[i][j] != 0) {
                cout.width(cellWidth);
                cout << grid[i][j];
            } else {
                cout.width(cellWidth);
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << " ";
    for (int j = 0; j < getGridSize(); j++) {
        cout << string(cellWidth, '-');  // Print the final row of horizontal lines
        if (j < getGridSize() - 1)
            cout << "-";
    }
    cout << endl;
}

void NumberGrid::move(InputHandler::Direction dir)
{
    if (dir == InputHandler::Direction::LEFT) {
        moveLeft();
    }
    if (!addRandomNumber()) {
        cout << "Game Over" << endl;
        exit(0);
    }

    printGrid();

    if (isGridFull()) {
        cout << "Game Over" << endl;
        exit(0);
    }
}


void NumberGrid::moveLeft()
{
    int gridSize = getGridSize();

    for (int i = 0; i < gridSize; ++i) {
        vector<int> newRow;
        
        // Collect all non-zero elements
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != 0) {
                newRow.push_back(grid[i][j]);
            }
        }
        
        // Add zeros to the end of the newRow
        while (newRow.size() < gridSize) {
            newRow.push_back(0);
        }
        
        // Copy newRow back to the grid
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = newRow[j];
        }
    }
}
