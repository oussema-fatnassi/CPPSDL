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
    } else if (dir == InputHandler::Direction::RIGHT) {
        moveRight();
    } else if (dir == InputHandler::Direction::UP) {
        moveUp();
    } else if (dir == InputHandler::Direction::DOWN) {
        moveDown();
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
        // Merge the row first
        merge(grid[i]);
        
        // Shift non-zero elements to the left after merging
        vector<int> newRow;

        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != 0) {
                newRow.push_back(grid[i][j]);
            }
        }

        // Fill the remaining spaces with zeros
        while (newRow.size() < gridSize) {
            newRow.push_back(0);
        }

        // Copy the new row back into the grid
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = newRow[j];
        }
    }
}


void NumberGrid::moveRight()
{
    int gridSize = getGridSize();

    for (int i = 0; i < gridSize; ++i) {
        // Reverse the row before merging to simulate moving right
        std::reverse(grid[i].begin(), grid[i].end());

        // Merge the reversed row
        merge(grid[i]);

        // Shift non-zero elements to the right after merging
        vector<int> newRow;

        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != 0) {
                newRow.push_back(grid[i][j]);
            }
        }

        // Fill the remaining spaces with zeros
        while (newRow.size() < gridSize) {
            newRow.push_back(0);
        }

        // Copy the new row back into the grid
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = newRow[j];
        }

        // Reverse the row back to its original order
        std::reverse(grid[i].begin(), grid[i].end());
    }
}


void NumberGrid::moveUp()
{
    int gridSize = getGridSize();

    for (int j = 0; j < gridSize; ++j) {
        vector<int> column;
        
        // Extract the column
        for (int i = 0; i < gridSize; ++i) {
            column.push_back(grid[i][j]);
        }

        // Merge the column
        merge(column);

        // Place the column back into the grid
        for (int i = 0; i < gridSize; ++i) {
            grid[i][j] = column[i];
        }
    }
}


void NumberGrid::moveDown()
{
    int gridSize = getGridSize();

    for (int j = 0; j < gridSize; ++j) {
        vector<int> column;

        // Extract the column
        for (int i = 0; i < gridSize; ++i) {
            column.push_back(grid[i][j]);
        }

        // Reverse the column for merging
        std::reverse(column.begin(), column.end());

        // Merge the reversed column
        merge(column);

        // Reverse the column back and place it into the grid
        std::reverse(column.begin(), column.end());

        // Place the column back into the grid
        for (int i = 0; i < gridSize; ++i) {
            grid[i][j] = column[i];
        }
    }
}


void NumberGrid::merge(vector<int>& row)
{
    int gridSize = getGridSize();

    for (int i = 0; i < gridSize - 1; ++i) {
        // If the current number and the next one are the same, merge them
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;            // Double the current cell value
            row[i + 1] = 0;          // Empty the next cell
            i++;                     // Skip the next cell to avoid double merging
        }
    }

    // After merging, move all numbers to the left (shift non-zero elements)
    vector<int> newRow;
    for (int i = 0; i < gridSize; ++i) {
        if (row[i] != 0) {
            newRow.push_back(row[i]);
        }
    }
    
    // Add zeros to the end of the newRow
    while (newRow.size() < gridSize) {
        newRow.push_back(0);
    }

    // Copy newRow back to the original row
    for (int i = 0; i < gridSize; ++i) {
        row[i] = newRow[i];
    }
}
