#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>
using namespace std;

class Grid {                                                // Grid class used for creating the game grid and handling game logic       
public: 
    Grid(int size);                                         // Constructor
    Grid();                                                 // Default constructor       
    ~Grid();                                                // Destructor       

    void handleInput(sf::Keyboard::Key key);                      // Public methods
    bool isGameOver() const;
    bool isGameWon();
    bool canMove() const;
    void undo();
    void reset();
    void move(int dx, int dy);
    bool addRandomNumber();                      
    bool isGridFull() const;                     
    
    bool gameWon = false;                                   // Member variables    

    vector<vector<int>> getGridData() const;                // Getters
    int getScore() const;
    int getSize() const;
    int getTileValue(int i, int j) const;

    void setGridData(const vector<vector<int>>& newGrid);   // Setters

private:
    void merge(vector<int>& row);                           // Private methods
    bool gridHasChanged() const;                       

    vector<vector<int>> grid;                               // Member variables    
    vector<vector<int>> previousGrid;
    int gridSize;
    int score;
    int previousScore;
    bool canUndo;
};


#endif // GRID_HPP