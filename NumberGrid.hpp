#ifndef NUMBERGRID_HPP
#define NUMBERGRID_HPP

#include "Grid.hpp"

class NumberGrid : public Grid
{
public:
    NumberGrid(int gridSize = 4);  
    void fillWith2048();
};

#endif // NUMBERGRID_HPP
