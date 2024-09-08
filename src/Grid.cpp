#include "Grid.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>

Grid::Grid(int gridSize) : gridSize(gridSize), grid(gridSize, vector<int>(gridSize, 0)) {
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    addRandomNumber(); // Add a second random number
}

Grid::~Grid() {}

bool Grid::addRandomNumber() {
    vector<pair<int, int>> emptyCells;

    // Find all empty cells
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
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
    int randValue = (rand() % 2 + 1) * 2; // Randomly pick 2 or 4

    grid[emptyCells[randIndex].first][emptyCells[randIndex].second] = randValue;

    return true;
}

bool Grid::isGridFull() const {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Grid::gridHasChanged() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != previousGrid[i][j]) {
                return true;  // Grid has changed
            }
        }
    }
    return false;  // Grid is unchanged
}

void Grid::move(int dx, int dy) {
    // Traverse grid in a way that ensures correct merging for each direction
    for (int i = 0; i < gridSize; ++i) {
        vector<int> line;

        // Extract row/column based on direction
        for (int j = 0; j < gridSize; ++j) {
            int x = i, y = j;
            if (dx == 0) { // Horizontal movement
                x = i;
                y = (dy > 0) ? gridSize - j - 1 : j; // Right or left
            } else { // Vertical movement
                x = (dx > 0) ? gridSize - j - 1 : j; // Down or up
                y = i;
            }

            if (grid[x][y] != 0) {
                line.push_back(grid[x][y]);
            }
        }

        // Merge numbers in the line
        merge(line);

        // Put merged line back into grid
        for (int j = 0; j < gridSize; ++j) {
            int x = i, y = j;
            if (dx == 0) { // Horizontal movement
                x = i;
                y = (dy > 0) ? gridSize - j - 1 : j; // Right or left
            } else { // Vertical movement
                x = (dx > 0) ? gridSize - j - 1 : j; // Down or up
                y = i;
            }

            if (j < line.size()) {
                grid[x][y] = line[j];
            } else {
                grid[x][y] = 0;
            }
        }
    }
}

void Grid::merge(vector<int>& line) {
    if (line.empty()) return;

    vector<int> mergedLine;

    for (size_t i = 0; i < line.size(); ++i) {
        if (i < line.size() - 1 && line[i] == line[i + 1]) {
            // Merge two adjacent numbers of the same value
            mergedLine.push_back(line[i] * 2);
            score += line[i] * 2;
            ++i; // Skip the next element since it's merged
        } else {
            mergedLine.push_back(line[i]);
        }
    }

    // Assign back the merged result to the original line
    line = mergedLine;
}

void Grid::handleInput(SDL_Keycode key) {
    previousGrid = grid;
    previousScore = score;

    // Determine the direction of movement
    if (key == SDLK_LEFT) {
        move(0, -1); // Move left
    } else if (key == SDLK_RIGHT) {
        move(0, 1);  // Move right
    } else if (key == SDLK_UP) {
        move(-1, 0); // Move up
    } else if (key == SDLK_DOWN) {
        move(1, 0);  // Move down
    }

    if (gridHasChanged()) {
        if (!addRandomNumber()) {
            cout << "Game Over" << endl;
        }
        canUndo = true;
    }
}

bool Grid::isGameOver() const {
    return isGridFull();
}

bool Grid::isGameWon() {
    if (!gameWon) {  
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] == 2048) {
                    gameWon = true;  
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grid::canMove() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 0) {
                return true;
            }
            if (i > 0 && grid[i][j] == grid[i - 1][j]) {
                return true;
            }
            if (i < gridSize - 1 && grid[i][j] == grid[i + 1][j]) {
                return true;
            }
            if (j > 0 && grid[i][j] == grid[i][j - 1]) {
                return true;
            }
            if (j < gridSize - 1 && grid[i][j] == grid[i][j + 1]) {
                return true;
            }
        }
    }
    return false;
}

int Grid::getScore() const {
    return score;
}

void Grid::undo() {
    if (canUndo) {
        grid = previousGrid;   
        score = previousScore; 
        canUndo = false;       
        cout << "Undo successful" << endl;
    } else {
        cout << "Undo not allowed" << endl;
    }
}

void Grid::reset() {
    grid = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));
    score = 0;
    addRandomNumber();
    addRandomNumber();
    canUndo = false;
    gameWon = false;  
    cout << "Grid reset" << endl;
}

