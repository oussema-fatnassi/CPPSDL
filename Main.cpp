#include "NumberGrid.hpp"
#include "InputHandler.hpp"
#include <iostream>

int main()
{
    NumberGrid numberGrid(4);
    numberGrid.printGrid();

    while (true) {
        InputHandler::Direction dir = InputHandler::getArrowKey();
        switch (dir) {
            case InputHandler::Direction::UP:
                cout << "Up Arrow Pressed" << endl;  
                numberGrid.move(InputHandler::Direction::UP);
                break;
            case InputHandler::Direction::DOWN:
                cout << "Down Arrow Pressed" << endl; 
                numberGrid.move(InputHandler::Direction::DOWN);
                break;
            case InputHandler::Direction::LEFT:
                cout << "Left Arrow Pressed" << endl;  
                numberGrid.move(InputHandler::Direction::LEFT);
                break;
            case InputHandler::Direction::RIGHT:
                cout << "Right Arrow Pressed" << endl;  
                numberGrid.move(InputHandler::Direction::RIGHT);
                break;
            default:
                break;
        }
    }
    return 0;
}
