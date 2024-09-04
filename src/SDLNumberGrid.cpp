#include "SDLNumberGrid.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

SDLNumberGrid::SDLNumberGrid(Window& window, int gridSize, int tileSize)
    : window(window), gridSize(gridSize), tileSize(tileSize), grid(gridSize, std::vector<int>(gridSize, 0)) {
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    addRandomNumber(); // Add a second random number
}

SDLNumberGrid::~SDLNumberGrid() {
    // Destructor
}

bool SDLNumberGrid::addRandomNumber() {
    std::vector<std::pair<int, int>> emptyCells;

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

bool SDLNumberGrid::isGridFull() const {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void SDLNumberGrid::handleInput(SDL_Keycode key) {
    if (key == SDLK_LEFT) {
        moveLeft();
    } else if (key == SDLK_RIGHT) {
        moveRight();
    } else if (key == SDLK_UP) {
        moveUp();
    } else if (key == SDLK_DOWN) {
        moveDown();
    }
    if (!addRandomNumber()) {
        std::cout << "Game Over" << std::endl;
    }
}

void SDLNumberGrid::moveLeft() {
    for (int i = 0; i < gridSize; ++i) {
        merge(grid[i]);
        // Shift non-zero elements to the left after merging
        std::vector<int> newRow;

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

void SDLNumberGrid::moveRight() {
    for (int i = 0; i < gridSize; ++i) {
        // Reverse the row before merging to simulate moving right
        std::reverse(grid[i].begin(), grid[i].end());
        merge(grid[i]);

        // Shift non-zero elements to the right after merging
        std::vector<int> newRow;

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

void SDLNumberGrid::moveUp() {
    for (int j = 0; j < gridSize; ++j) {
        std::vector<int> column;

        // Extract the column
        for (int i = 0; i < gridSize; ++i) {
            column.push_back(grid[i][j]);
        }

        merge(column);

        // Place the column back into the grid
        for (int i = 0; i < gridSize; ++i) {
            grid[i][j] = column[i];
        }
    }
}

void SDLNumberGrid::moveDown() {
    for (int j = 0; j < gridSize; ++j) {
        std::vector<int> column;

        // Extract the column
        for (int i = 0; i < gridSize; ++i) {
            column.push_back(grid[i][j]);
        }

        // Reverse the column for merging
        std::reverse(column.begin(), column.end());
        merge(column);

        // Reverse the column back and place it into the grid
        std::reverse(column.begin(), column.end());

        for (int i = 0; i < gridSize; ++i) {
            grid[i][j] = column[i];
        }
    }
}

void SDLNumberGrid::merge(std::vector<int>& row) {
    int gridSize = this->gridSize;

    // Shift non-zero elements to the left
    std::vector<int> newRow;
    for (int i = 0; i < gridSize; ++i) {
        if (row[i] != 0) {
            newRow.push_back(row[i]);
        }
    }

    while (newRow.size() < gridSize) {
        newRow.push_back(0);
    }

    // Merge adjacent elements if they are the same
    for (int i = 0; i < gridSize - 1; ++i) {
        if (newRow[i] != 0 && newRow[i] == newRow[i + 1]) {
            newRow[i] *= 2;         // Double the current cell value
            newRow[i + 1] = 0;      // Empty the next cell
            i++;                    // Skip the next cell to avoid double merging
        }
    }

    // Shift again to move non-zero elements to the left after merging
    std::vector<int> finalRow;
    for (int i = 0; i < gridSize; ++i) {
        if (newRow[i] != 0) {
            finalRow.push_back(newRow[i]);
        }
    }

    while (finalRow.size() < gridSize) {
        finalRow.push_back(0);
    }

    row = finalRow;
}

void SDLNumberGrid::render() {
    // Clear the window first
    window.clear();

    // Loop through the grid and render each tile
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int x = xStart + j * tileSize;
            int y = yStart + i * tileSize;
            renderTile(grid[i][j], x, y);
        }
    }

    // Present the rendered frame
    window.present();
}

void SDLNumberGrid::renderTile(int value, int x, int y) {
    GameObject tile(window.getRenderer(), value, x, y, tileSize, tileSize);
    tile.render(window.getRenderer());
}

bool SDLNumberGrid::isGameOver() const {
    return isGridFull();
}
