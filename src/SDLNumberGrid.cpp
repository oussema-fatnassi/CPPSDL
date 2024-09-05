#include "SDLNumberGrid.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

SDLNumberGrid::SDLNumberGrid(Window& window, int gridSize, int tileSize)
    : window(window), gridSize(gridSize), tileSize(tileSize), grid(gridSize, std::vector<int>(gridSize, 0)),
      xStart(75), yStart(300), offsetX(10), offsetY(8), score(0) {  // Set to match the background position
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    addRandomNumber(); // Add a second random number

    // Initialize font and text color
    font = TTF_OpenFont("../assets/fonts/ClearSansBold.ttf", 40);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    textColor = {255, 255, 255}; 
    textColor2 = { 113, 112, 107};
}


SDLNumberGrid::~SDLNumberGrid() {
    if (font) {
        TTF_CloseFont(font);
    }
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
    bool moved = false;

    previousGrid = grid;
    previousScore = score;

    if (key == SDLK_LEFT) {
        moveLeft();
        moved = true;
    } else if (key == SDLK_RIGHT) {
        moveRight();
        moved = true;
    } else if (key == SDLK_UP) {
        moveUp();
        moved = true;
    } else if (key == SDLK_DOWN) {
        moveDown();
        moved = true;
    }

    if (moved) {
        if (!addRandomNumber()) {
            std::cout << "Game Over" << std::endl;
        }
        canUndo = true;
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
            newRow[i] *= 2;            // Double the current cell value
            score += newRow[i];         // Add the merged value to the score
            newRow[i + 1] = 0;          // Empty the next cell
            i++;                        // Skip the next cell to avoid double merging
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


const int TILE_GAP = 10;

void SDLNumberGrid::render() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // Calculate x and y with the tile gap
            int x = xStart + j * (tileSize + TILE_GAP) + offsetX;
            int y = yStart + i * (tileSize + TILE_GAP) + offsetY;
            renderTile(grid[i][j], x, y);
        }
    }
}


void SDLNumberGrid::renderTile(int value, int x, int y) {
    // Render the tile background
    GameObject tile(window.getRenderer(), value, x, y, tileSize, tileSize);
    tile.render(window.getRenderer());

    // Render the text in the center of the tile
    if (value != 0) {
        std::string text = std::to_string(value);
        SDL_Color color;

        // Choose the text color based on the value
        if (value <= 8) {
            color = textColor2;  // Use textColor2 for values less than or equal to 8
        } else {
            color = textColor;  // Use the default textColor for values greater than 8
        }

        // Create the text surface with the selected color
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        
        if (textSurface) {
            // Create the texture from the surface
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
            SDL_FreeSurface(textSurface);

            if (textTexture) {
                // Calculate the position to center the text
                int textWidth, textHeight;
                SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

                SDL_Rect textRect;
                textRect.x = x + (tileSize - textWidth) / 2;
                textRect.y = y + (tileSize - textHeight) / 2;
                textRect.w = textWidth;
                textRect.h = textHeight;

                // Render the text
                SDL_RenderCopy(window.getRenderer(), textTexture, nullptr, &textRect);
                SDL_DestroyTexture(textTexture);
            }
        }
    }
}

bool SDLNumberGrid::isGameOver() const {
    return isGridFull();
}

bool SDLNumberGrid::canMove() const {
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

void SDLNumberGrid::writeText(const std::string& text, TTF_Font* font, SDL_Color color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) {
        std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect = {x, y, 0, 0};
    SDL_QueryTexture(textTexture, nullptr, nullptr, &dstRect.w, &dstRect.h);

    SDL_RenderCopy(window.getRenderer(), textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
}

int SDLNumberGrid::getScore() const {
    return score;
}

void SDLNumberGrid::undo() {
    if (canUndo) {
        grid = previousGrid;   
        score = previousScore; 
        canUndo = false;       
        cout << "Undo successful" << endl;
    } else {
        cout << "Undo not allowed" << endl;
    }
}

void SDLNumberGrid::reset() {
    grid = vector<vector<int>>(gridSize, vector<int>(gridSize, 0));
    score = 0;
    addRandomNumber();
    addRandomNumber();
    canUndo = false;  
    cout << "Grid reset" << endl;
}
