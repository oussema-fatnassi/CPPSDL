#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

class InputHandler
{
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

    static Direction getArrowKey();
};

#endif // INPUTHANDLER_HPP
