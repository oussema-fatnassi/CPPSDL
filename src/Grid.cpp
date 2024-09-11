#include "Grid.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>

Grid::Grid(int gridSize) : gridSize(gridSize), grid(gridSize, vector<int>(gridSize, 0)) {
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    cout << "Grid created" << endl;
    addRandomNumber(); // Add a second random number
}

Grid::Grid() : Grid(4) {}

Grid::~Grid() {}

bool Grid::addRandomNumber() {
    vector<pair<int, int>> emptyCells;

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

    int randIndex = rand() % emptyCells.size();
    int randValue = (rand() % 2 + 1) * 512; // Randomly pick 2 or 4

    grid[emptyCells[randIndex].first][emptyCells[randIndex].second] = randValue;

    cout << "Random number added" << endl;
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
                cout << "Grid has changed" << endl;
                return true;  // Grid has changed
            }
        }
    }
    cout << "Grid has not changed" << endl;
    return false;  // Grid is unchanged
}

void Grid::move(int dx, int dy) {
    for (int i = 0; i < gridSize; ++i) {
        vector<int> line;

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

        merge(line);

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
            mergedLine.push_back(line[i] * 2);
            score += line[i] * 2;
            ++i; 
        } else {
            mergedLine.push_back(line[i]);
        }
    }

    line = mergedLine;
}

void Grid::handleInput(SDL_Keycode key) {
    cout << "Handling input: " << key << endl;
    previousGrid = grid;
    previousScore = score;

    if (key == SDLK_LEFT) {
        move(0, -1);
    } else if (key == SDLK_RIGHT) {
        move(0, 1);
    } else if (key == SDLK_UP) {
        move(-1, 0);
    } else if (key == SDLK_DOWN) {
        move(1, 0);
    }

    if (gridHasChanged()) {
        if (!addRandomNumber()) {
            cout << "Game Over" << std::endl;
        }
        canUndo = true;  
    } else {
        cout << "Grid did not change, undo disabled" << endl;
        canUndo = false; 
    }
}



bool Grid::isGameOver() const {
    cout << "Checking if game is over" << endl;
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

vector<vector<int>> Grid::getGridData() const {
    return grid;
}

void Grid::setGridData(const vector<vector<int>>& newGrid) {
    grid = newGrid;
}

int Grid::getSize() const {
    return gridSize;
}

int Grid::getTileValue(int i, int j) const {
    return grid[i][j];
}