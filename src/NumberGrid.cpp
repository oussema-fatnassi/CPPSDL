#include "NumberGrid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

NumberGrid::NumberGrid(int gridSize) : Grid(gridSize), grid(gridSize, vector<int>(gridSize, 0)), score(0) {
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    addRandomNumber(); // Add a second random number
}

bool NumberGrid::addRandomNumber() {
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
        return false; // No empty cells available
    }

    // Select a random empty cell
    int randIndex = rand() % emptyCells.size();
    int randValue = (rand() % 2 + 1) * 2; // Randomly pick 2 or 4

    grid[emptyCells[randIndex].first][emptyCells[randIndex].second] = randValue;

    return true;
}

void NumberGrid::move(InputHandler::Direction dir) {
    bool moved = false;
    switch (dir) {
        case InputHandler::Direction::LEFT:
            moved = moveLeft();
            break;
        case InputHandler::Direction::RIGHT:
            moved = moveRight();
            break;
        case InputHandler::Direction::UP:
            moved = moveUp();
            break;
        case InputHandler::Direction::DOWN:
            moved = moveDown();
            break;
        default:
            break;
    }

    // If a move was made, add a random number
    if (moved) {
        addRandomNumber();
    }

    // Optional: Check if the grid is full
    if (isGridFull()) {
        std::cout << "Game Over" << std::endl;
    }
}

bool NumberGrid::moveLeft() {
    bool moved = false;
    for (int i = 0; i < getGridSize(); ++i) {
        vector<int> row = grid[i];
        merge(row); // Merges tiles and updates the row
        if (row != grid[i]) {
            moved = true;
            grid[i] = row;
        }
    }
    return moved;
}

bool NumberGrid::moveRight() {
    bool moved = false;
    for (int i = 0; i < getGridSize(); ++i) {
        vector<int> row = grid[i];
        reverse(row.begin(), row.end());
        merge(row);
        reverse(row.begin(), row.end());
        if (row != grid[i]) {
            moved = true;
            grid[i] = row;
        }
    }
    return moved;
}

bool NumberGrid::moveUp() {
    bool moved = false;
    for (int j = 0; j < getGridSize(); ++j) {
        vector<int> column;
        for (int i = 0; i < getGridSize(); ++i) {
            column.push_back(grid[i][j]);
        }
        merge(column);
        for (int i = 0; i < getGridSize(); ++i) {
            if (grid[i][j] != column[i]) moved = true;
            grid[i][j] = column[i];
        }
    }
    return moved;
}

bool NumberGrid::moveDown() {
    bool moved = false;
    for (int j = 0; j < getGridSize(); ++j) {
        vector<int> column;
        for (int i = 0; i < getGridSize(); ++i) {
            column.push_back(grid[i][j]);
        }
        reverse(column.begin(), column.end());
        merge(column);
        reverse(column.begin(), column.end());
        for (int i = 0; i < getGridSize(); ++i) {
            if (grid[i][j] != column[i]) moved = true;
            grid[i][j] = column[i];
        }
    }
    return moved;
}
bool NumberGrid::isGridFull() {
    for (int i = 0; i < getGridSize(); i++) {
        for (int j = 0; j < getGridSize(); j++) {
            if (grid[i][j] == 0) {
                return false; // Grid is not full if there is at least one empty cell
            }
        }
    }
    return true; // Grid is full
}
void NumberGrid::merge(std::vector<int>& row) {
    int gridSize = getGridSize();

    // Step 1: Shift non-zero elements to the left (remove gaps)
    std::vector<int> newRow;
    for (int i = 0; i < gridSize; ++i) {
        if (row[i] != 0) {
            newRow.push_back(row[i]);
        }
    }

    // Fill the remaining spaces with zeros
    while (newRow.size() < gridSize) {
        newRow.push_back(0);
    }

    // Step 2: Merge adjacent elements if they are the same
    for (int i = 0; i < gridSize - 1; ++i) {
        if (newRow[i] != 0 && newRow[i] == newRow[i + 1]) {
            newRow[i] *= 2;         // Double the current cell value
            score += newRow[i];     // Update score when merging tiles
            newRow[i + 1] = 0;      // Empty the next cell
            i++;                    // Skip the next cell to avoid double merging
        }
    }

    // Step 3: Shift again to move non-zero elements to the left after merging
    std::vector<int> finalRow;
    for (int i = 0; i < gridSize; ++i) {
        if (newRow[i] != 0) {
            finalRow.push_back(newRow[i]);
        }
    }

    // Fill the remaining spaces with zeros
    while (finalRow.size() < gridSize) {
        finalRow.push_back(0);
    }

    // Copy the finalRow back to the original row
    for (int i = 0; i < gridSize; ++i) {
        row[i] = finalRow[i];
    }
}
const vector<vector<int>>& NumberGrid::getGrid() const {
    return grid;
}
