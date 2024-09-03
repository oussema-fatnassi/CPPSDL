#include <iostream>
#include "Window.cpp"

int main()
{
    Window window("Testing", 600, 800);

    while (!window.isClosed())
    {
        window.pollEvents();
    }

    return 0;
}