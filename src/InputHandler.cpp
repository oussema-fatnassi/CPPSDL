#include "InputHandler.hpp"
#include <iostream>

#ifdef _WIN32
#include <conio.h> // Windows specific header

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

InputHandler::Direction InputHandler::getArrowKey()
{
    int c = _getch(); // Read character without waiting for Enter

    switch(c) {
        case KEY_UP:
            return Direction::UP;
        case KEY_DOWN:
            return Direction::DOWN;
        case KEY_LEFT:
            return Direction::LEFT;
        case KEY_RIGHT:
            return Direction::RIGHT;
        default:
            return Direction::NONE;
    }
}

#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

InputHandler::Direction InputHandler::getArrowKey()
{
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON; // Disable buffering
    newt.c_lflag &= ~ECHO;   // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar(); // Read the first character

    if (ch == '\033') { // Escape sequence
        getchar(); // Skip the [
        switch (getchar()) { // Read the next character
            case 'A': return Direction::UP;
            case 'B': return Direction::DOWN;
            case 'C': return Direction::RIGHT;
            case 'D': return Direction::LEFT;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    return Direction::NONE;
}
#endif
