#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL.h>

class Window
{
public:
    Window(const char *title, int width, int height);
    ~Window();

    bool isClosed() const;
    void pollEvents();

private:
    SDL_Window *m_window;
    bool m_isClosed;
};

#endif // WINDOW_HPP