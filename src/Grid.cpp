#include "Grid.hpp"

Grid::Grid(int gridSize) : gridSize(gridSize), grid(gridSize, vector<int>(gridSize, 0)) {       // Constructor with grid size
    srand(time(0));                                                                             // Seed for random number generation
    addRandomNumber(); 
    addRandomNumber(); 
}

Grid::Grid() : Grid(4) {}                                                                       // Default constructor with default grid size of 4          

Grid::~Grid() {}                                                                                // Destructor

bool Grid::addRandomNumber() {                                                                  // Method to add a random number to the grid
    vector<pair<int, int>> emptyCells;

    for (int i = 0; i < gridSize; i++) {                                                        // Iterate through the grid to find empty cells          
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    if (emptyCells.empty()) {                                                                   // If no empty cells are found, return false           
        return false;
    }

    int randIndex = rand() % emptyCells.size();
    int randValue = (rand() % 2 + 1) * 512;                                                       // Randomly pick 2 or 4

    grid[emptyCells[randIndex].first][emptyCells[randIndex].second] = randValue;                // Add the random number to the grid    
    return true;
}

bool Grid::isGridFull() const {                                                                 // Method to check if the grid is full
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Grid::gridHasChanged() const {                                                             // Method to check if the grid has changed since the last move
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != previousGrid[i][j]) {
                return true;                                                                    // Grid has changed
            }
        }
    }
    return false;                                                                               // Grid is unchanged
}

void Grid::move(int dx, int dy) {                                                               // Method to move the tiles in the grid based on direction
    for (int i = 0; i < gridSize; ++i) {
        vector<int> line;                                                                       // Vector to store the values of the current row or column

        for (int j = 0; j < gridSize; ++j) {
            int x = i, y = j;
            if (dx == 0) {                                                                      // Horizontal movement
                x = i;
                y = (dy > 0) ? gridSize - j - 1 : j;                                            // Right or left
            } else {                                                                            // Vertical movement
                x = (dx > 0) ? gridSize - j - 1 : j;                                            // Down or up
                y = i;
            }

            if (grid[x][y] != 0) {                                                              // Add non-zero values to the line vector
                line.push_back(grid[x][y]);
            }
        }

        merge(line);                                                                            // Merge the values in the line vector

        for (int j = 0; j < gridSize; ++j) {
            int x = i, y = j;
            if (dx == 0) {                                                                      // Horizontal movement
                x = i;
                y = (dy > 0) ? gridSize - j - 1 : j;                                            // Right or left
            } else {                                                                            // Vertical movement
                x = (dx > 0) ? gridSize - j - 1 : j;                                            // Down or up
                y = i;
            }

            if (j < line.size()) {                                                              // Update the grid with the merged values
                grid[x][y] = line[j];
            } else {
                grid[x][y] = 0;
            }
        }
    }
}

void Grid::merge(vector<int>& line) {                                                           // Method to merge the values in the line vector
    if (line.empty()) return;                                                                   // Return if the line is empty

    vector<int> mergedLine;

    for (size_t i = 0; i < line.size(); ++i) {                                                  
        if (i < line.size() - 1 && line[i] == line[i + 1]) {                                    // Merge adjacent values if they are equal
            mergedLine.push_back(line[i] * 2);
            score += line[i] * 2;                                                               // Update the score
            ++i; 
        } else {
            mergedLine.push_back(line[i]);
        }
    }

    line = mergedLine;
}

void Grid::handleInput(sf::Keyboard::Key key) {                                                 // Method to handle input from the user
    previousGrid = grid;
    previousScore = score;

 if (key == sf::Keyboard::Left) {
        move(0, -1);  // Move left
    } else if (key == sf::Keyboard::Right) {
        move(0, 1);   // Move right
    } else if (key == sf::Keyboard::Up) {
        move(-1, 0);  // Move up
    } else if (key == sf::Keyboard::Down) {
        move(1, 0);   // Move down
    }

    if (gridHasChanged()) {                                                                     // Check if the grid has changed after the move and add a random number
        if (!addRandomNumber()) {
        }
        canUndo = true;  
    } else {
        canUndo = false; 
    }
}

bool Grid::isGameOver() const {                                                                 // Method to check if the game is over
    return isGridFull();
}

bool Grid::isGameWon() {                                                                        // Method to check if the game is won, if the player reaches 2048
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

bool Grid::canMove() const {                                                                    // Method to check if the player can make a move
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 0) {                                                              // Check if there are empty cells
                return true;
            }
            if (i > 0 && grid[i][j] == grid[i - 1][j]) {                                        // Check if there are adjacent cells with the same value
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

void Grid::undo() {                                                                             // Method to undo the last move
    if (canUndo) {
        grid = previousGrid;   
        score = previousScore; 
        canUndo = false;       
    }
}

void Grid::reset() {                                                                            // Method to reset the grid     
    grid = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));                             // Reset the grid to all zeros
    score = 0;
    addRandomNumber();
    addRandomNumber();
    canUndo = false;
    gameWon = false;  
}

int Grid::getScore() const {                                                                    // Getters
    return score;
}

int Grid::getSize() const {
    return gridSize;
}

int Grid::getTileValue(int i, int j) const {
    return grid[i][j];
}

vector<vector<int>> Grid::getGridData() const {
    return grid;
}

void Grid::setGridData(const vector<vector<int>>& newGrid) {                                    // Setters  
    grid = newGrid;
}
