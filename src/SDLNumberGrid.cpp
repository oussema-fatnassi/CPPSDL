#include "SDLNumberGrid.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Assets.hpp"

SDLNumberGrid::SDLNumberGrid(Window& window, int gridSize, int tileSize)
    : window(window), gridSize(gridSize), tileSize(tileSize), grid(gridSize, vector<int>(gridSize, 0)),
      xStart(75), yStart(300), offsetX(10), offsetY(8), score(0) {  // Set to match the background position
    srand(time(0)); // Seed for random number generation
    addRandomNumber(); // Start by adding a random 2 or 4
    addRandomNumber(); // Add a second random number

    // Initialize font and text color
    font = TTF_OpenFont(FONT_PATH.c_str(), 40);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
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

bool SDLNumberGrid::gridHasChanged() const {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] != previousGrid[i][j]) {
                return true;  // Grid has changed
            }
        }
    }
    return false;  // Grid is unchanged
}


void SDLNumberGrid::move(int dx, int dy) {
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

void SDLNumberGrid::merge(vector<int>& line) {
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

void SDLNumberGrid::handleInput(SDL_Keycode key) {
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
        string text = to_string(value);
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

bool SDLNumberGrid::isGameWon() {
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

void SDLNumberGrid::writeText(const string& text, TTF_Font* font, SDL_Color color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) {
        cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.getRenderer(), textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) {
        cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << endl;
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
    gameWon = false;  
    cout << "Grid reset" << endl;
}
