#include "NumberGrid.hpp"
#include <iostream>
using namespace std;

int main()
{
    NumberGrid numberGrid(4);
    numberGrid.printGrid();

    char input;
    while (true) {
        cout << "Press any key to simulate a move: ";
        cin >> input;  
        numberGrid.move(); 
    }
    return 0;
}
