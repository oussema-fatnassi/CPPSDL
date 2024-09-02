#ifndef GRID_HPP
#define GRID_HPP

class Grid
{
private:
    int gridSize;
public:
    Grid(int gridSize);
    ~Grid();
    void printGrid();
    int getGridSize();
};


#endif // GRID_HPP